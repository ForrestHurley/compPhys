#ifndef AVOIDING_RANDOM_WALK
#define AVOIDING_RANDOM_WALK

#include "random_walk.h"
#include "point_hash.h"
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <algorithm>

template <int N, class point_type>
class avoiding_random_walk : public random_walk_with_memory<N, point_type>
{
private:
  int num_without_move = 0;
  int maximum_steps_acheived = 0;
  int num_without_progress = 0;

  std::unordered_multimap<std::array<int, N>, std::pair<std::array<point_type, N>, int>, int_array_hash<N>> location_multimap;

  std::array<int, N> map_key(std::array<point_type, N> point);

  template<int R, class S>
  class is_collision_impl { public: static bool _(std::array<S, R> point, avoiding_random_walk *p, int &colliding_point_index) { return false; } };

  bool is_collision(std::array<point_type, N> point, int &colliding_point_index);
  bool is_collision(std::array<point_type, N> point);

  template<int, class>
  class step_backwards_impl { public: static void _(avoiding_random_walk *p) { } };

  template<int R>
  class step_backwards_impl<R, double> { public: static void _(avoiding_random_walk *p); };

  template<int R>
  class step_backwards_impl<R, int> { public: static void _(avoiding_random_walk *p); };

  void step_backwards();
  void step_backwards(int n);

  static bool get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y,
    double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y);

public:
  int max_without_move = 5;
  int max_without_progress = 20;
  bool preserve_n = true;
  unsigned int test_direction_count = 4;

  using random_walk_with_memory<N, point_type>::step_walk;
  void step_walk() override;
};

template <int N, class point_type>
std::array<int, N> avoiding_random_walk<N, point_type>::map_key(std::array<point_type, N> point)
{
	std::array<int, N> key;
	for (unsigned int i = 0; i < point.size(); i++) key[i] = point[i];
	return key;
};

template<int N, class point_type>
template<int R>
class avoiding_random_walk<N, point_type>::is_collision_impl<R, int>
{
public:
  static bool _(std::array<int, R> point, avoiding_random_walk<R, int> *p, int &colliding_point_index)
  {
    if (p->location_multimap.count(p->map_key(point)) > 0)
    {
      auto range = p->location_multimap.equal_range(p->map_key(point));
      std::pair<std::array<int, R>, int> first_point = range.first;
      colliding_point_index = first_point.second;

      return true;
    }
    return false;
  }
};

template<int N, class point_type>
template<int R>
class avoiding_random_walk<N, point_type>::is_collision_impl<R, double>
{
public:
  static bool _(std::array<double, R> point, avoiding_random_walk<R, double> *p, int &colliding_point_index)
  {
    return false;
  }
};

template<>
template<>
class avoiding_random_walk<2, double>::is_collision_impl<2, double>
{
public:
  static bool _(std::array<double, 2> point, avoiding_random_walk<2, double> *p, int &colliding_point_index)
  {
    std::array<int, 2> key = p->map_key(point);
    std::array<double, 2> previous_point = p->get_history_at(p->get_total_steps() - 1);

    std::vector<std::pair<std::array<double, 2>, int>> keyed_points;

    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        std::array<int, 2> grid_key = key;
        grid_key[0] += (i - 1);
        grid_key[1] += (j - 1);

        auto range = p->location_multimap.equal_range(grid_key);
        for (auto ii = range.first; ii != range.second; ++ii)
          if (ii->second.second != p->get_total_steps() - 2)
            keyed_points.push_back(ii->second);
      }
    }

    std::vector<std::pair<std::pair<std::array<double, 2>, std::array<double, 2>>, int>> line_list;

    for (std::pair<std::array<double, 2>, int> pnt_idx : keyed_points)
    {
      if (pnt_idx.second + 2 < p->get_total_steps() - 1) //We don't want to use the last point in the history (seen later as previous_point)
      {
        line_list.push_back(std::make_pair(std::make_pair(pnt_idx.first, p->get_history_at(pnt_idx.second + 2)), pnt_idx.second + 2));
      }
      line_list.push_back(std::make_pair(std::make_pair(p->get_history_at(pnt_idx.second), pnt_idx.first), pnt_idx.second));
    }

    for (std::pair<std::pair<std::array<double, 2>, std::array<double, 2>>, int> test_line : line_list)
    {
      double intersect_x, intersect_y;

      if (avoiding_random_walk::get_line_intersection(previous_point[0], previous_point[1], point[0], point[1],
        test_line.first.first[0], test_line.first.first[1], test_line.first.second[0], test_line.first.second[1],
        &intersect_x, &intersect_y))
      {
        colliding_point_index = test_line.second;
        return true;
      }
    }

    return false;
  }
};

template<int N, class point_type>
bool avoiding_random_walk<N, point_type>::is_collision(std::array<point_type, N> point, int &colliding_point_index) 
{
  return is_collision_impl<N, point_type>::_(point, this, colliding_point_index);
}

template<int N, class point_type>
bool avoiding_random_walk<N, point_type>::is_collision(std::array<point_type, N> point) 
{
  int tmp;
  return is_collision_impl<N, point_type>::_(point, this, tmp);
}

template<int N, class point_type>
template<int R>
void avoiding_random_walk<N, point_type>::step_backwards_impl<R, int>::_(avoiding_random_walk<N, point_type> *p)
{
  p->pop_last_location();
};

template<int N, class point_type>
template<int R>
void avoiding_random_walk <N, point_type>::step_backwards_impl<R, double>::_(avoiding_random_walk<N, point_type> *p)
{
  const std::array<double, R> last_loc = p->get_last_location();

  auto range = p->location_multimap.equal_range(p->map_key(last_loc));
  for (auto ii = range.first; ii != range.second; ++ii)
  {
    if (ii->second.second == p->get_total_steps() - 1)
    {
      p->location_multimap.erase(ii);
      break;
    }
  }
  p->pop_last_location();
};

template <int N, class point_type>
void avoiding_random_walk<N, point_type>::step_backwards()
{
  step_backwards_impl<N, point_type>::_(this);
};

template <int N, class point_type>
void avoiding_random_walk<N, point_type>::step_backwards(int n)
{
  for (int i = 0; i < n; i++) step_backwards();
};

// This function taken from https://stackoverflow.com/a/1968345
// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
template <int N, class point_type>
bool avoiding_random_walk<N, point_type>::get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y,
  double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y)
{
  double s1_x, s1_y, s2_x, s2_y;
  s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
  s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

  double s, t;
  s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
  t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
  {
    // Collision detected
    if (i_x != NULL)
      *i_x = p0_x + (t * s1_x);
    if (i_y != NULL)
      *i_y = p0_y + (t * s1_y);
    return 1;
  }

  return 0; // No collision
};

template <int N, class point_type>
void avoiding_random_walk<N, point_type>::step_walk()
{
  random_walk_with_memory<N, point_type>::step_walk();
  
  if (this->get_total_steps() > maximum_steps_acheived)
  {
    maximum_steps_acheived = this->get_total_steps();
    num_without_progress = 0;
  }

  if (is_collision(this->get_last_location()))
  {
    //std::cout << "Collision" << std::endl;
    this->pop_last_location();
    num_without_move++;

    if (num_without_move >= max_without_move)
    {
      if (num_without_progress >= max_without_progress)
      {
        std::vector<int> colliding_indices;
        this->steps--;
        while(colliding_indices.size() < test_direction_count)
        {
          std::array<point_type, N> test_point = this->generate_single_step();
          
          int colliding_index;
          if (is_collision(test_point, colliding_index))
            colliding_indices.push_back(colliding_index);
        }
        this->steps++;

        int maximum_index = *std::max_element(colliding_indices.begin(), colliding_indices.end()); 
        int delta_index = this->get_total_steps() - maximum_index;

        step_backwards(delta_index);
        num_without_progress = 0;
        
        int num_to_move = num_without_move;
        num_without_move = 0;
        for (int i = 0; i < delta_index + num_to_move; i++)
          step_walk();
      }
      else
      {
        const int number_of_backsteps = pow(num_without_progress / max_without_move, 0.5) - (maximum_steps_acheived - this->get_total_steps());

        for (int i = 0; i < number_of_backsteps; i++)
          avoiding_random_walk<N, point_type>::step_backwards();
        num_without_move += number_of_backsteps;

        if (preserve_n)
        { //There is a really really small chance that this will die with some error right at the beginning
          int num_to_move = num_without_move;
          num_without_move = 0;
          for (int i = 0; i < num_to_move; i++)
            step_walk();
        }
      }
    }
  }
  else
  {
    location_multimap.insert(std::make_pair(
      map_key(this->get_last_location()),
      std::make_pair(
        this->get_last_location(),
        this->get_total_steps() - 1)));

    if (preserve_n && num_without_move > 0)
    {
      int num_to_step = num_without_move;
      num_without_move = 0;
      for (int i = 0; i < num_to_step; i++)
        step_walk();
    }
  }
  num_without_progress++;
  //this->write_to_file("outfile_tmp.csv");
};

#endif

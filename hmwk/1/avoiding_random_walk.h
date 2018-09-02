#ifndef AVOIDING_RANDOM_WALK
#define AVOIDING_RANDOM_WALK

#include "random_walk.h"
#include "point_hash.h"
#include <unordered_map>
#include <iostream>
#include <cassert>

template <int N, class point_type>
class avoiding_random_walk : public random_walk_with_memory<N, point_type>
{
private:
  int num_without_move = 0;

  std::unordered_multimap<std::array<int, N>, std::pair<std::array<point_type, N>, int>, int_array_hash<N>> location_multimap;

  std::array<int, N> map_key(std::array<point_type, N> point);

  template<int R, class S>
  class is_collision_impl { public: static bool _(std::array<S, R> point, avoiding_random_walk *p) { return false; } };

  bool is_collision(std::array<point_type, N> point) { return is_collision_impl<N, point_type>::_(point, this); }
  
  template<int, class>
  class step_backwards_impl { public: static void _(avoiding_random_walk *p) { } };

  void step_backwards() { step_backwards_impl<N, point_type>::_(this); };

  static bool get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y,
    double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y);

public:
  int max_without_move = 20;
  bool preserve_n = true;

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
  static bool _(std::array<int, R> point, avoiding_random_walk *p)
  {
    return p->location_multimap.count(p->map_key(point)) > 0;
  }
};

template<int N, class point_type>
template<int R>
class avoiding_random_walk<N, point_type>::is_collision_impl<R, double>
{
public:
  static bool _(std::array<double, R> point, avoiding_random_walk *p)
  {
    return false;
  }
};

template<>
template<>
class avoiding_random_walk<2, double>::is_collision_impl<2, double>
{
public:
  static bool _(std::array<double, 2> point, avoiding_random_walk *p)
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
        //std::cout << key[0] << ":" << key[1] << std::endl;

        auto range = p->location_multimap.equal_range(grid_key);
        for (auto ii = range.first; ii != range.second; ++ii)
          if (ii->second.second != p->get_total_steps() - 2)
            keyed_points.push_back(ii->second);
      }
    }

    /*std::cout << std::endl;
    for (auto elem : keyed_points)
    std::cout << elem.first[0] << "," << elem.first[1] << "," << elem.second << " ";
    std::cout << std::endl;*/

    //std::cout << std::endl << keyed_points.size() << std::endl;

    std::vector<std::pair<std::array<double, 2>, std::array<double, 2>>> line_list;

    for (std::pair<std::array<double, 2>, int> pnt_idx : keyed_points)
    {
      //std::cout << pnt_idx.first[0] << ", " << pnt_idx.first[1] << ": " << pnt_idx.second << std::endl;
      //std::cout << "||" << pnt_idx.first[0] << ", " << pnt_idx.first[1] << " cc " << p->get_history_at(pnt_idx.second + 1)[0] << ", " << p->get_history_at(pnt_idx.second + 1)[1] << std::endl;
      if (pnt_idx.second + 2 < p->get_total_steps() - 1) //We don't want to use the last point in the history (seen later as previous_point)
      {
        //std::cout << "dk " << pnt_idx.second + 2 << " : " << p->get_history_at(pnt_idx.second + 2)[0] << std::endl;
        line_list.push_back(std::make_pair(pnt_idx.first, p->get_history_at(pnt_idx.second + 2)));
      }
      line_list.push_back(std::make_pair(pnt_idx.first, p->get_history_at(pnt_idx.second)));
    }

    //std::cout << "Line list size: " << line_list.size() << std::endl;

    //if (p->get_total_steps() % 1000 == 0)
    //  std::cout << line_list.size() << std::endl;

    //std::cout << previous_point[0] << ", " << point[0] << std::endl;

    for (std::pair<std::array<double, 2>, std::array<double, 2>> test_line : line_list)
    {
      //TODO: Check for parallel lines

      /*double max_x = std::min(std::max(previous_point[0], point[0]), std::max(test_line.first[0], test_line.second[0]));
      double min_x = std::max(std::min(previous_point[0], point[0]), std::min(test_line.first[0], test_line.second[0]));
      double max_y = std::min(std::max(previous_point[0], point[0]), std::max(test_line.first[1], test_line.second[1]));
      double min_y = std::max(std::min(previous_point[0], point[0]), std::min(test_line.first[1], test_line.second[1]));

      double t =
      ((test_line.first[0] - previous_point[0]) * (test_line.second[1] - test_line.first[1])
      - (test_line.first[1] - previous_point[1]) * (test_line.second[0] - test_line.first[0])) /
      ((test_line.second[0] - test_line.first[0]) * (point[1] - previous_point[1])
      - (test_line.second[1] - test_line.first[1]) * (point[0] - previous_point[0]));

      double intersect_x = (point[0] - previous_point[0]) * t + previous_point[0];
      double intersect_y = (point[1] - previous_point[1]) * t + previous_point[1];

      std::cout << "x: " << min_x << ", " << max_x << " y: " << min_y << ", " << max_y << std::endl;
      std::cout << "intersect: " << intersect_x << ", " << intersect_y << std::endl;

      if (min_x < intersect_x && max_x > intersect_x
      && min_y < intersect_y && max_y > intersect_y)
      {
      return true;
      }*/

      double intersect_x, intersect_y;

      //std::cout << std::setprecision(3) << std::endl << previous_point[0] << ", " << previous_point[1] << ", " << point[0] << ", " << point[1] << " | " <<
      //    test_line.first[0] << ", " << test_line.first[1] << ", " << test_line.second[0] << ", " << test_line.second[1] << std::endl;

      if (avoiding_random_walk::get_line_intersection(previous_point[0], previous_point[1], point[0], point[1],
        test_line.first[0], test_line.first[1], test_line.second[0], test_line.second[1],
        &intersect_x, &intersect_y))
      {
        //std::cout << "Intersect" << std::endl;
        return true;
      }
    }

    return false;
  }
};

template<int N, class point_type>
template<int R>
class avoiding_random_walk<N, point_type>::step_backwards_impl<R, int>
{
public:
  static void _(avoiding_random_walk *p)
  {
    p->pop_last_location();
  }
};

template<int N, class point_type>
template<int R>
class avoiding_random_walk <N, point_type>::step_backwards_impl<R, double>
{
public:
  static void _(avoiding_random_walk *p)
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
  }
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

  if (is_collision(this->get_last_location()))
  {
    //std::cout << "Collision" << std::endl;
    this->pop_last_location();
    num_without_move++;

    if (num_without_move >= max_without_move)
    {
      step_backwards();

      if (preserve_n)
      { //There is a really really small chance that this will die with some error right at the beginning
        int num_to_move = num_without_move;
        num_without_move = std::max(0, num_without_move - 2);
        for (int i = 0; i < num_to_move - num_without_move + 1; i++)
          step_walk();
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
  this->write_to_file("outfile_tmp.csv");
};

#endif

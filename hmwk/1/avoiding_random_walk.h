#ifndef AVOIDING_RANDOM_WALK
#define AVOIDING_RANDOM_WALK

#include "random_walk.h"
#include "point_hash.h"
#include <unordered_map>
#include <iostream>

template <int N, class point_type>
class avoiding_random_walk : public random_walk_with_memory<N, point_type>
{
private:
  int num_without_move = 0;

  std::unordered_multimap<std::array<int, N>, std::pair<std::array<point_type, N>, int>, int_array_hash<N>> location_multimap;

  std::array<int, N> map_key(std::array<point_type, N> point)
  {
    std::array<int, N> key;
    for (uint i = 0; i < point.size(); i++) key[i] = point[i];
    return key;
  }

  template<int R, class S>
  class is_collision_impl { public: static bool _(std::array<S, R> point, avoiding_random_walk *p) { return false; } };

  template<int R>
  class is_collision_impl<R, int>
  {
    public:
    static bool _(std::array<int, R> point, avoiding_random_walk *p)
    {
      return p->location_multimap.count(p->map_key(point)) > 0;
    }
  };

  template<int R>
  class is_collision_impl<R, double>
  {
    public:
    static bool _(std::array<double, R> point, avoiding_random_walk *p)
    {
      return false;
    }
  };

  bool is_collision(std::array<point_type, N> point) { return is_collision_impl<N, point_type>::_(point, this); }
  
  template<int, class>
  class step_backwards_impl { public: static void _(avoiding_random_walk *p) { } };

  template<int R>
  class step_backwards_impl<R, int>
  {
    public:
    static void _(avoiding_random_walk *p)
    {
      p->pop_last_location();
    }
  };

  template<int R>
  class step_backwards_impl<R, double>
  {
    public:
    static void _(avoiding_random_walk *p) { }
  };

  void step_backwards() { step_backwards_impl<N, point_type>::_(this); };

public:
  int max_without_move = 10;
  bool preserve_n = true;

  using random_walk_with_memory<N, point_type>::step_walk;
  void step_walk() override
  {
    random_walk_with_memory<N, point_type>::step_walk();

    if (is_collision(this->get_last_location()))
    {
      this->pop_last_location();
      num_without_move++;

      if (num_without_move == max_without_move)
      {
        step_backwards();
        if (preserve_n) 
        { //There is a really really small chance that this will die with some error right at the beginning
          num_without_move = 0;
          for (int i = 0; i < max_without_move + 1; i++)
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

    std::vector<std::pair<std::array<double, 2>, int>> keyed_points;

    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        std::array<int, 2> grid_key = key;
        key[0] += (i - 1);
        key[1] += (j - 1);

        auto range = p->location_multimap.equal_range(grid_key);
        for (auto ii = range.first; ii != range.second; ++ii)
          keyed_points.push_back(ii->second);
      }
    }

    std::vector<std::pair<std::array<double, 2>, std::array<double, 2>>> line_list;

    for (std::pair<std::array<double, 2>, int> pnt_idx : keyed_points)
    {

      if (pnt_idx.second + 1 < p->get_total_steps())
        line_list.push_back( std::make_pair( pnt_idx.first, p->get_history_at(pnt_idx.second + 1) ));
      if (pnt_idx.second > 0)
        line_list.push_back( std::make_pair( pnt_idx.first, p->get_history_at(pnt_idx.second - 1) ));
    }

    //if (p->get_total_steps() % 1000 == 0)
    //  std::cout << line_list.size() << std::endl;
    std::array<double, 2> previous_point = p->get_history_at(p->get_total_steps() - 2);

    for (std::pair<std::array<double, 2>, std::array<double, 2>> test_line : line_list)
    {
      //TODO: Check for parallel lines

      double max_x = std::min(std::max(previous_point[0], point[0]), std::max(test_line.first[0], test_line.second[0]));
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

      if (min_x < intersect_x && max_x > intersect_x
        && min_y < intersect_y && max_y > intersect_y)
      {
        return true;
      }
    }

    return false;
  }
};

#endif

#ifndef LATTICE_AVOIDING_WALK
#define LATTICE_AVOIDING_WALK

#include "random_walk.h"
#include "point_hash.h"
#include <unordered_map>
#include <iostream>

template <int N>
class lattice_walk
{
public:
  using point = std::array<int, N>

private:
  std::vector<point> location_list;

protected:
  point generate_nth_step(int index);
  std::array<int, N * 2> generate_all_steps();
  point generate_random_step();

  virtual void push_point(point in_point);
  virtual point pop_point();
  
  virtual bool step_forwards(int steps);
  virtual void step_backwards(int steps);

public:
  lattice_walk();

  void make_walk(int steps);

  int get_length();

  std::vector<point> get_location_list();
  point get_single_location(int index);
}

template <int N>
class avoiding_lattice_walk : public lattice_walk<N>
{
private:
  std::unordered_set<point, int_array_hash<N>> location_set;

protected:
  void push_point(point in_point) override;
  point pop_point() override;

  virtual generate_random_step();

  virtual bool step_forwards(int steps) override;
  virtual void step_backwards(int steps) override;

public:
  avoiding_lattice_walk();
}

template <int N>
class avoiding_distributed_lattice_walk : public avoiding_lattice_walk<N>
{
protected:
  point generate_random_step() override;

  virtual std::array<int, N * 2> find_direction_counts(int depth = 0);
}

template <int N>
class avoiding_counting_lattice_walk : public avoiding_distributed_lattice_walk<N>
{
private:
  int maximum_depth = 10;

protected:
  std::array<int, N * 2> find_direction_counts(int depth = 0) override;
}

template <int N>
class avoiding_random_lattice_walk : public avoiding_distributed_lattice_walk<N>
{
private:
  int exponential_steps = 1;
  int branching_factor = 100;
  int maximum_depth = 200;

protected:
  std::array<int, N * 2> find_direction_counts(int depth = 0) override;
}

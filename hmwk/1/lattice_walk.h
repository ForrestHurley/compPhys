#ifndef LATTICE_WALK
#define LATTICE_WALK

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
lattice_walk<N>::lattice_walk();

template <int N>
lattice_walk<N>::point lattice_walk<N>::generate_nth_step(int index);

template <int N>
std::array<int, N * 2> lattice_walk<N>::generate_all_steps();

template <int N>
lattice_walk<N>::point lattice_walk<N>::generate_random_step();

template <int N>
virtual void point_lattice<N>::push_point(point_lattice<N>::point in_point);

template <int N>
virtual point_lattice<N>::point point_lattice<N>::pop_point();

template <int N>
virtual bool point_lattice<N>::step_forwards(int steps);

template <int N>
virtual void point_lattice<N>::step_backwards(int steps);

template <int N>
void point_lattice<N>::make_walk(int steps);

template <int N>
int point_lattice<N>::get_length();

template <int N>
std::vector<point_lattice<N>::point> point_lattice<N>::get_location_list();

template <int N>
point_lattice<N>::point point_lattice<N>::get_single_location(int index);

#endif

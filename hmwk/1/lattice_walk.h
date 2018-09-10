#ifndef LATTICE_WALK
#define LATTICE_WALK

#include "random_walk.h"
#include "point_hash.h"
#include <unordered_map>

template <int N>
class lattice_walk : public random_walk<int, N>
{
protected:
  point generate_nth_step(int index);
  std::array<int, N * 2> generate_all_steps();
  point generate_random_step() override;
}

template <int N>
lattice_walk<N>::point lattice_walk<N>::generate_nth_step(int index);

template <int N>
std::array<int, N * 2> lattice_walk<N>::generate_all_steps();

template <int N>
lattice_walk<N>::point lattice_walk<N>::generate_random_step();

#endif

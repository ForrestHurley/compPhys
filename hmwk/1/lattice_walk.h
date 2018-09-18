#ifndef LATTICE_WALK
#define LATTICE_WALK

#include "random_walk.h"

template <int N>
class lattice_walk : public random_walk<int, N>
{
protected:
  std::array<int, N> generate_nth_step(int index);
  std::vector<std::array<int, N>> generate_all_steps();
  std::array<int, N> generate_random_step() override;
};

template <int N>
std::array<int, N> lattice_walk<N>::generate_nth_step(int index)
{
  int direction = (index % 2) * 2 - 1;
  int dim_index = index / 2;  

  std::array<int, N> step = this->get_zero_point();
  step[dim_index] = direction;

  return step;
}

template <int N>
std::vector<std::array<int, N>> lattice_walk<N>::generate_all_steps()
{
  std::vector<std::array<int, N>> out;
  out.reserve(2 * N);

  for (int i = 0; i < 2 * N; i++)
    out.push_back(generate_nth_step(i));

  return out;
}

template <int N>
std::array<int, N> lattice_walk<N>::generate_random_step()
{
  static thread_local std::mt19937_64 engine(time(0));
  static thread_local std::uniform_int_distribution<int> distribution(0, N * 2 - 1);

  return generate_nth_step(distribution(engine));
}

#endif

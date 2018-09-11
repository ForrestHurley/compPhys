#ifndef FAST_SELF_AVOIDING_WALK
#define FAST_SELF_AVOIDING_WALK

#include "avoiding_lattice_walk.h"

template <int N>
class avoiding_distributed_lattice_walk : public avoiding_lattice_walk<N>
{
protected:
  std::array<int, N> generate_random_step() override;

  virtual std::array<int, N * 2> find_direction_counts(int depth = 0) = 0;
};

template <int N>
class avoiding_counting_lattice_walk : public avoiding_distributed_lattice_walk<N>
{
private:
  int maximum_depth = 10;

protected:
  std::array<int, N * 2> find_direction_counts(int depth = 0) override;
};

template <int N>
class avoiding_random_lattice_walk : public avoiding_distributed_lattice_walk<N>
{
private:
  int exponential_steps = 1;
  int branching_factor = 100;
  int maximum_depth = 200;

protected:
  std::array<int, N * 2> find_direction_counts(int depth = 0) override;
};

template <int N>
std::array<int, N> avoiding_distributed_lattice_walk<N>::generate_random_step()
{
  std::array<int, N * 2> direction_counts = find_direction_counts();

  static thread_local std::mt19937_64 engine(time(0));
  std::discrete_distribution<int> distribution (direction_counts.begin(), direction_counts.end());

  return this->generate_nth_step(distribution(engine));
}

template <int N>
std::array<int, N * 2> avoiding_counting_lattice_walk<N>::find_direction_counts(int depth)
{

}

template <int N>
std::array<int, N * 2> avoiding_random_lattice_walk<N>::find_direction_counts(int depth)
{

}

#endif

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
  int maximum_depth = 18;

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
  std::array<int, N * 2> out;
  for (int i = 0; i < N * 2; i++)
    out[i] = 0;

  if (depth < maximum_depth)
  {
    auto step_list = this->generate_all_steps();

    for (int idx = 0; idx < N * 2; idx ++)
    {
      if (this->take_step(step_list[idx]))
      {
        std::array<int, N * 2> temp_counts = find_direction_counts(depth + 1);
        out[idx] = std::accumulate(temp_counts.begin(), temp_counts.end(), 0);
        this->pop_point();
      }
    }
  }
  else
  {
    out[0] = 1;
  }

  return out;
}

template <int N>
std::array<int, N * 2> avoiding_random_lattice_walk<N>::find_direction_counts(int depth)
{

}

#endif

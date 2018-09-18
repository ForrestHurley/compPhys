#ifndef GAUSSIAN_WALK
#define GAUSSIAN_WALK

#include "random_walk.h"
#include <random>

template <int N>
class gaussian_walk : public random_walk<double, N>
{
protected:
  std::array<double, N> generate_random_step() override;
  std::array<double, N> raw_random_step();
};

template <int N>
class normalized_gaussian_walk : public gaussian_walk<N>
{
protected:
  std::array<double, N> generate_random_step() override; 
  std::array<double, N> normalized_step(std::array<double, N> raw_step);
};

template <int N>
std::array<double, N> gaussian_walk<N>::generate_random_step()
{
  return raw_random_step();
}

template <int N>
std::array<double, N> gaussian_walk<N>::raw_random_step()
{
  static thread_local std::mt19937_64 engine(time(0));
  static thread_local std::normal_distribution<double> distribution(0., 1.);

  std::array<double, N> out;
  for (int i = 0; i < N; i++)
    out[i] = distribution(engine);

  return out;
}

template <int N>
std::array<double, N> normalized_gaussian_walk<N>::generate_random_step()
{
  return normalized_step(this->raw_random_step());
}

template <int N>
std::array<double, N> normalized_gaussian_walk<N>::normalized_step(std::array<double, N> raw_step)
{
  double length = 0;
  for (int i = 0; i < N; i++)
    length += raw_step[i] * raw_step[i];

  length = sqrt(length);

  for (int i = 0; i < N; i++)
    raw_step[i] /= length;

  return raw_step;
}

#endif

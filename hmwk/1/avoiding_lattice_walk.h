#ifndef AVOIDING_RANDOM_WALK
#define AVOIDING_RANDOM_WALK

#include "lattice_walk.h"
#include <unordered_set>

template <int N>
class avoiding_lattice_walk : public lattice_walk<N>
{
private:
  std::unordered_set<std::array<int, N>, int_array_hash<N>> location_set;

protected:
  void push_point(std::array<int, N> in_point) override;
  void pop_point() override;

  virtual bool step_forwards(int steps) override;

  bool check_collision(std::array<int, N> new_point);
};

template <int N>
void avoiding_lattice_walk<N>::push_point(std::array<int, N> in_point)
{
  random_walk<int, N>::push_point(in_point);
  location_set.insert(in_point);
}

template <int N>
void avoiding_lattice_walk<N>::pop_point()
{
  location_set.erase(this->get_last_location());
  random_walk<int, N>::pop_point();
}

template <int N>
bool avoiding_lattice_walk<N>::step_forwards(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    std::array<int, N> random_step = this->generate_random_step();
    std::array<int, N> new_location = this->get_last_location();

    for (int j = 0; j < N; j++)
    {
      new_location[j] += random_step[j];
    }

    if (check_collision(new_location))
      return false; 

    push_point(new_location);
  }
  return true;
}

template <int N>
bool avoiding_lattice_walk<N>::check_collision(std::array<int, N> new_point)
{
  return location_set.count(new_point) > 0;
}

#endif

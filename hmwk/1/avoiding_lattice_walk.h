#ifndef AVOIDING_RANDOM_WALK
#define AVOIDING_RANDOM_WALK

#include "lattice_walk.h"

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

std::unordered_set<point, int_array_hash<N>> location_set;

void push_point(point in_point) override;
point pop_point() override;

virtual generate_random_step();

virtual bool step_forwards(int steps) override;
virtual void step_backwards(int steps) override;

avoiding_lattice_walk();

#endif

#ifndef LENNARD_JONES_POTENTIAL_H
#define LENNARD_JONES_POTENTIAL_H

#include "pairwise_potential_function.h"

class LennardJonesPotential : public PairwisePotentialFunction
{
public:
  const double potential_depth;
  const double maximum_potential_distance;

  explicit LennardJonesPotential(double potential_depth = 1., double maximum_potential_distance = 1.);

  double getPotential(double distance) const override;
  Coordinate getPartials(const Coordinate& displacement) const override;
};

#endif

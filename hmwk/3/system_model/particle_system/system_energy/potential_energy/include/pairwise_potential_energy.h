#ifndef PAIRWISE_POTENTIAL_ENERGY_H
#define PAIRWISE_POTENTIAL_ENERGY_H

#include "potential_energy.h"
#include "pairwise_potential_function.h"

class PairwisePotentialEnergy : public PotentialEnergy
{
protected:
  const PairwisePotentialFunction& pairwise_potential;
public:
  PairwisePotentialEnergy(
    const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
    const PairwisePotentialFunction& pairwise_potential);
};

#endif

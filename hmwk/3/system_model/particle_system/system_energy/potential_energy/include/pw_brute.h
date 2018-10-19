#ifndef PW_BRUTE_H
#define PW_BRUTE_H

#include "pairwise_potential_energy.h"

class PairwiseBruteForcePotentialEnergy : public PairwisePotentialEnergy
{
public:
  PairwiseBruteForcePotentialEnergy(const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
    const PairwisePotentialFunction& pairwise_potential);

  double getPotentialEnergy() override;
  std::vector<Coordinate> getPartials() override;
};

#endif

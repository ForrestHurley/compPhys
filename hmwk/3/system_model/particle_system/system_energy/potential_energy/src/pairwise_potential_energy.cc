#include "pairwise_potential_energy.h"

PairwisePotentialEnergy::PairwisePotentialEnergy(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential) :
  PotentialEnergy(locations), pairwise_potential(pairwise_potential) {}


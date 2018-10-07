#include "pw_brute.h"

PairwiseBruteForcePotentialEnergy::PairwiseBruteForcePotentialEnergy(const std::vector<MetricSpace::MetricPoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential) :
  PairwisePotentialEnergy(locations, pairwise_potential) {}

double PairwiseBruteForcePotentialEnergy::getPotentialEnergy()
{
  return 0.;
}

std::vector<double> PairwiseBruteForcePotentialEnergy::getPartials()
{
  return std::vector<double>();
}


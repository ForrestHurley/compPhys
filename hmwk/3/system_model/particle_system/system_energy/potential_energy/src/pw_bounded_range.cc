#include "pw_bounded_range.h"

PairwiseBoundedRangePotentialEnergy::PairwiseBoundedRangePotentialEnergy(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential, const FixedRadiusNearestNeighbor& nearest_neighbor)
  : PairwisePotentialEnergy(locations, pairwise_potential), nearest_neighbor(nearest_neighbor) {}

double PairwiseBoundedRangePotentialEnergy::getPotentialEnergy()
{
  return 0.;
}

std::vector<double> PairwiseBoundedRangePotentialEnergy::getPartials()
{
  return std::vector<double>();
}

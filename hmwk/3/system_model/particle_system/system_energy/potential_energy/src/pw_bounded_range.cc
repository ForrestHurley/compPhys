#include "pw_bounded_range.h"

PairwiseBoundedRangePotentialEnergy::PairwiseBoundedRangePotentialEnergy(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential, const FixedRadiusNearestNeighbor& nearest_neighbor)
  : PairwisePotentialEnergy(locations, pairwise_potential), nearest_neighbor(nearest_neighbor) {}

double PairwiseBoundedRangePotentialEnergy::getPotentialEnergy() const
{
  return 0.;
}

std::vector<Coordinate> PairwiseBoundedRangePotentialEnergy::getPartials() const
{
  return std::vector<Coordinate>();
}

#include "pw_lattice_grid.h"

PairwiseLatticeGridPotentialEnergy::PairwiseLatticeGridPotentialEnergy(
  const std::vector<EuclideanSpace::EuclideanPoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential) :
  converted_locations(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>(locations.begin(), locations.end())),
  PairwisePotentialEnergy(converted_locations, pairwise_potential),
  coordinate_bins(std::vector<int>()) {} 

double PairwiseLatticeGridPotentialEnergy::getPotentialEnergy()
{
  return 0.;
}

std::vector<Coordinate> PairwiseLatticeGridPotentialEnergy::getPartials()
{
  return std::vector<Coordinate>();
}

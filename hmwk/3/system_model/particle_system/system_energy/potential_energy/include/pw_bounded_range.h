#ifndef PW_BOUNDED_RANGE_H
#define PW_BOUNDED_RANGE_H

#include "fixed_radius_nn.h"
#include "pairwise_potential_energy.h"

class PairwiseBoundedRangePotentialEnergy : public PairwisePotentialEnergy
{
private:
  const FixedRadiusNearestNeighbor& nearest_neighbor;
public:
  PairwiseBoundedRangePotentialEnergy(
    const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
    const PairwisePotentialFunction& pairwise_potential, const FixedRadiusNearestNeighbor& nearest_neighbor);

  double getPotentialEnergy() const override;
  std::vector<Coordinate> getPartials() const override;
};

#endif

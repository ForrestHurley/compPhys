#ifndef PW_LATTICE_GRID_H
#define PW_LATTICE_GRID_H

#include "euclidean_space.h"
#include "binned_coordinates.h"
#include "pairwise_potential_energy.h"

class PairwiseLatticeGridPotentialEnergy : public PairwisePotentialEnergy
{
private:
  BinnedCoordinates coordinate_bins;
  std::vector<double> lattice_energies;
  std::vector<MetricSpace::MetricPoint*> converted_locations;

public:
  PairwiseLatticeGridPotentialEnergy(const std::vector<EuclideanSpace::EuclideanPoint*>& locations,
    const PairwisePotentialFunction& pairwise_potential);

  double getPotentialEnergy() override;
  std::vector<double> getPartials() override;
};

#endif

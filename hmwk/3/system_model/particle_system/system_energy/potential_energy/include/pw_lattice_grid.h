#ifndef PW_LATTICE_GRID_H
#define PW_LATTICE_GRID_H

#include "euclidean_space.h"
#include "binned_coordinates.h"

class PairwiseLatticeGridPotentialEnergy : public PairwisePotentialEnergy
{
private:
  BinnedCoordinates coordinate_bins;
  std::vector<double> lattice_energies;
public:
  PairwiseLatticeGridPotentialEnergy(const std::vector<EuclideanSpace::EuclideanPoint*>& locations,
    const PairwisePotentialFunction& pairwise_potential);

  double getPotentialEnergy() override;
  std::vector<double> getPartials() override;
};

#endif

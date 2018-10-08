#ifndef POTENTIAL_ENERGY_H
#define POTENTIAL_ENERGY_H

#include <vector>
#include "smooth_coordinate_space.h"

class PotentialEnergy
{
protected:
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations;
public:
  PotentialEnergy(const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations);

  virtual double getPotentialEnergy() = 0;
  virtual std::vector<double> getPartials() = 0;
};

#endif

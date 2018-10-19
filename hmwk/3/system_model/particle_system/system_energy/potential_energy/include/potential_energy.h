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

  virtual double getPotentialEnergy() const = 0;
  virtual std::vector<Coordinate> getPartials() const = 0;
};

#endif

#ifndef POTENTIAL_ENERGY_H
#define POTENTIAL_ENERGY_H

#include <vector>
#include "coordinate.h"

class PotentialEnergy
{
protected:
  const std::vector<MetricSpace::MetricPoint*>& locations;
public:
  PotentialEnergy(const std::vector<MetricSpace::MetricPoint*>& locations);

  virtual double getPotentialEnergy() = 0;
  virtual std::vector<double> getPartials() = 0;
};

#endif

#ifndef PAIRWISE_POTENTIAL_FUNCTION_H
#define PAIRWISE_POTENTIAL_FUNCTION_H

#include "coordinate.h"

class PairwisePotentialFunction
{
public:
  virtual double getPotential(double distance) const = 0;
  virtual Coordinate getPartials(const Coordinate& displacement) const = 0;
}; 

#endif

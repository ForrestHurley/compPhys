#ifndef PAIRWISE_POTENTIAL_FUNCTION_H
#define PAIRWISE_POTENTIAL_FUNCTION_H

#include "coordinate.h"

class PairwisePotentialFunction
{
public:
  virtual double getPotential(const Coordinate& A, const Coordinate& B) const = 0;
  virtual Coordinate getPartials(const Coordinate& A, const Coordinate& B) const = 0;
}; 

#endif

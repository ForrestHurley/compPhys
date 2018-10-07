#ifndef PAIRWISE_POTENTIAL_FUNCTION_H
#define PAIRWISE_POTENTIAL_FUNCTION_H

#include "coordinate.h"

class PairwisePotentialFunction
{
public:
  virtual double getPotential(const Coordinate& A, const Coordinate& B) = 0;
  virtual std::vector<double> getPartials(const Coordinate& A, const Coordinate& B) = 0;
}; 

#endif

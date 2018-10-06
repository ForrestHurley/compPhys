#ifndef PAIRWISE_POTENTIAL_FUNCTION_H
#define PAIRWISE_POTENTIAL_FUNCTION_H

#include "coordinate.h"

class PairwisePotentialFunction
{
public:
  double getPotential(const Coordinate& A, const Coordinate& B);
  std::vector<double> getPartials(const Coordinate& A, const Coordinate& B);
}; 

#endif

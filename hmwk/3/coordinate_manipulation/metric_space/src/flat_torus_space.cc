
#include "flat_torus_space.h"

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(const std::vector<double>& bounds) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(bounds) {}

FlatTorusSpace::FlatTorusSpace(std::vector<double> bounds) :
  BoundedEuclideanSpace(bounds), flat_torus_origin(bounds) {}

const FlatTorusSpace::FlatTorusPoint& FlatTorusSpace::getOrigin()
{
  return flat_torus_origin;
}

double FlatTorusSpace::Distance(const EuclideanPoint& A, const EuclideanPoint& B)
{
  return 0.;
}

double FlatTorusSpace::Distance(const FlatTorusPoint& A, const FlatTorusPoint& B)
{
  return 0.;
}

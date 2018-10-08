
#include "flat_torus_space.h"

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(const std::vector<double>& bounds) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(bounds) {}

FlatTorusSpace::FlatTorusSpace(std::vector<double> bounds) :
  BoundedEuclideanSpace(bounds), flat_torus_origin(bounds) {}

const FlatTorusSpace::FlatTorusPoint& FlatTorusSpace::getOrigin() const
{
  return flat_torus_origin;
}

double FlatTorusSpace::Distance(const MetricPoint& A, const MetricPoint& B) const
{
  return 0.;
}


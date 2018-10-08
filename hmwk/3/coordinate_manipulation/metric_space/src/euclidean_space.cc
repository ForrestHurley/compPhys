
#include "euclidean_space.h"

EuclideanSpace::EuclideanPoint::EuclideanPoint(unsigned int dimension) :
    SmoothCoordinatePoint(dimension) {}

EuclideanSpace::EuclideanSpace(unsigned int dimension) : 
  SmoothCoordinateSpace(dimension),
  coordinate_origin(dimension) {}

double EuclideanSpace::Distance(const MetricPoint& A, const MetricPoint& B) const
{
  return 0.;
}

const EuclideanSpace::EuclideanPoint& EuclideanSpace::getOrigin() const
{
  return coordinate_origin;
}

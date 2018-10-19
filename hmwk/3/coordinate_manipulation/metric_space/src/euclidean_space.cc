
#include "euclidean_space.h"

EuclideanSpace::EuclideanPoint::EuclideanPoint(unsigned int dimension) :
  SmoothCoordinatePoint(dimension) {}

EuclideanSpace::EuclideanPoint::EuclideanPoint(const Coordinate& coordinate) :
  SmoothCoordinatePoint(coordinate) {}

EuclideanSpace::EuclideanSpace(unsigned int dimension) : 
  SmoothCoordinateSpace(dimension),
  coordinate_origin(dimension) {}

EuclideanSpace::EuclideanSpace(const Coordinate& zero_coordinate) :
  SmoothCoordinateSpace(zero_coordinate),
  coordinate_origin(zero_coordinate) {}

double EuclideanSpace::Distance(const MetricPoint& A, const MetricPoint& B) const
{
  const EuclideanPoint& a_euclidean = 
    dynamic_cast<const EuclideanPoint&>(A);
  const EuclideanPoint& b_euclidean = 
    dynamic_cast<const EuclideanPoint&>(B);

  return (a_euclidean.getCoordinate() - b_euclidean.getCoordinate).getMagnitude(); 
}

const EuclideanSpace::EuclideanPoint& EuclideanSpace::getOrigin() const
{
  return coordinate_origin;
}


#include "euclidean_space.h"

EuclideanSpace::EuclideanPoint::EuclideanPoint(
  EuclideanSpace* space) :
  SmoothCoordinatePoint(space) {}

EuclideanSpace::EuclideanPoint::EuclideanPoint(
  EuclideanSpace* space, const Coordinate& coordinate) :
  SmoothCoordinatePoint(space, coordinate) {}

EuclideanSpace::EuclideanSpace(unsigned int dimension) : 
  SmoothCoordinateSpace(dimension),
  coordinate_origin(this, Coordinate::Zero(dimension)) {}

EuclideanSpace::EuclideanSpace(const Coordinate& zero_coordinate) :
  SmoothCoordinateSpace(zero_coordinate),
  coordinate_origin(this, zero_coordinate) {}

double EuclideanSpace::Distance(const MetricPoint& A, const MetricPoint& B) const
{
  const SmoothCoordinatePoint& a_coordinate = 
    dynamic_cast<const SmoothCoordinatePoint&>(A);
  const SmoothCoordinatePoint& b_coordinate = 
    dynamic_cast<const SmoothCoordinatePoint&>(B);

  return DisplacementVector(a_coordinate, b_coordinate).getMagnitude(); 
}

Coordinate EuclideanSpace::DisplacementVector(
  const SmoothCoordinatePoint& A, const SmoothCoordinatePoint& B) const 
{
  return A.getCoordinate() - B.getCoordinate(); 
}

const EuclideanSpace::EuclideanPoint& EuclideanSpace::getOrigin() const
{
  return coordinate_origin;
}

EuclideanSpace::EuclideanPoint& EuclideanSpace::CreatePoint(
  const Coordinate& coordinate)
{
  EuclideanPoint* point = new EuclideanPoint(this, coordinate);
  addPoint(point);
  return *point;
}

#include "smooth_coordinate_space.h"

SmoothCoordinateSpace::SmoothCoordinatePoint::SmoothCoordinatePoint(unsigned int dimension) :
  dimension(dimension), coordinate(dimension) {}

Coordinate SmoothCoordinateSpace::SmoothCoordinatePoint::getCoordinate() const
{
  return Coordinate(dimension);
}

void SmoothCoordinateSpace::SmoothCoordinatePoint::setCoordinate(const Coordinate& newCoordinate) {}

SmoothCoordinateSpace::SmoothCoordinateSpace(unsigned int dimension) :
  dimension(dimension), coordinate_origin(dimension) {}

const SmoothCoordinateSpace::SmoothCoordinatePoint& SmoothCoordinateSpace::getOrigin() const
{
  return coordinate_origin;
}

#include "smooth_coordinate_space.h"

SmoothCoordinateSpace::SmoothCoordinatePoint::SmoothCoordinatePoint(unsigned int dimension) :
  dimension(dimension), coordinate(dimension) {}

SmoothCoordinateSpace::SmoothCoordinatePoint::SmoothCoordinatePoint(const Coordinate& coordinate) :
  coordinate(coordinate), dimension(coordinate.dimension) {}

const Coordinate& SmoothCoordinateSpace::SmoothCoordinatePoint::getCoordinate() const
{
  return coordinate;
}

void SmoothCoordinateSpace::SmoothCoordinatePoint::setCoordinate(const Coordinate& newCoordinate) 
{
  coordinate = newCoordinate;
}

SmoothCoordinateSpace::SmoothCoordinateSpace(unsigned int dimension) :
  dimension(dimension), coordinate_origin(Coordinate::Zero(dimension)) {}

SmoothCoordinateSpace::SmoothCoordinateSpace(const Coordinate& zero_coordinate) :
  coordinate_origin(zero_coordinate), dimension(coordinate_origin.dimension) {}

const SmoothCoordinateSpace::SmoothCoordinatePoint& SmoothCoordinateSpace::getOrigin() const
{
  return coordinate_origin;
}

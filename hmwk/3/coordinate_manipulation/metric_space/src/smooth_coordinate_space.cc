#include "smooth_coordinate_space.h"
#include <assert.h>

SmoothCoordinateSpace::SmoothCoordinatePoint::SmoothCoordinatePoint(SmoothCoordinateSpace* space) :
  MetricPoint(space), coordinate(getDimension()) {}

SmoothCoordinateSpace::SmoothCoordinatePoint::SmoothCoordinatePoint(
  SmoothCoordinateSpace* space, const Coordinate& coordinate) :
  MetricPoint(space),
  coordinate(coordinate) 
{
  assert(coordinate.dimension == getDimension());
}

const Coordinate& SmoothCoordinateSpace::SmoothCoordinatePoint::getCoordinate() const
{
  return coordinate;
}

void SmoothCoordinateSpace::SmoothCoordinatePoint::setCoordinate(const Coordinate& newCoordinate) 
{
  coordinate = newCoordinate;
}

int SmoothCoordinateSpace::SmoothCoordinatePoint::getDimension() const
{
  return getSpace()->getDimension();
}

SmoothCoordinateSpace::SmoothCoordinateSpace(unsigned int dimension) :
  dimension(dimension), coordinate_origin(this, Coordinate::Zero(dimension)) {}

SmoothCoordinateSpace::SmoothCoordinateSpace(const Coordinate& zero_coordinate) :
  dimension(zero_coordinate.dimension), coordinate_origin(this, zero_coordinate) {}

const SmoothCoordinateSpace::SmoothCoordinatePoint& SmoothCoordinateSpace::getOrigin() const
{
  return coordinate_origin;
}


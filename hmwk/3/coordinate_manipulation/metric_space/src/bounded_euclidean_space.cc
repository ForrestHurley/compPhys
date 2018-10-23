
#include "bounded_euclidean_space.h"
#include <assert.h>
#include <iostream>

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(
  BoundedEuclideanSpace* space, const CoordinateBounds& bounds) :
  EuclideanPoint(space,
    bounds.ClampCoordinate(Coordinate::Zero(bounds.getDimension()))),
  bounds(bounds)
{
  assert(getDimension() == bounds.getDimension());  
}

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(
  BoundedEuclideanSpace* space,
  const CoordinateBounds& bounds,
  const Coordinate& coordinate) :
  EuclideanPoint(space, bounds.ClampCoordinate(coordinate)),
  bounds(bounds)
{
  assert(bounds.getDimension() == coordinate.dimension);
  assert(getDimension() == bounds.getDimension());
}

void BoundedEuclideanSpace::BoundedEuclideanPoint::setCoordinate(const Coordinate& new_coordinate)
{
  //std::cout << new_coordinate << " : " <<
  //  bounds.ClampCoordinate(new_coordinate) << std::endl;
  EuclideanPoint::setCoordinate(
    bounds.ClampCoordinate(new_coordinate));
}

BoundedEuclideanSpace::BoundedEuclideanSpace(const CoordinateBounds& bounds) :
  EuclideanSpace(bounds.getDimension()), bounds(bounds),
  bounded_euclidean_origin(this, bounds) {}

BoundedEuclideanSpace::BoundedEuclideanSpace(const CoordinateBounds& bounds,
  const Coordinate& zero_coordinate) :
  EuclideanSpace(zero_coordinate), bounds(bounds),
  bounded_euclidean_origin(this, bounds, zero_coordinate)
{
  assert(bounds.getDimension() == zero_coordinate.dimension);
}

const BoundedEuclideanSpace::BoundedEuclideanPoint& BoundedEuclideanSpace::getOrigin() const
{
  return bounded_euclidean_origin;
}

BoundedEuclideanSpace::BoundedEuclideanPoint& BoundedEuclideanSpace::CreatePoint(
  const Coordinate& coordinate)
{
  BoundedEuclideanPoint* point = new BoundedEuclideanPoint(this, bounds, coordinate);
  addPoint(point);
  return *point;
}

const CoordinateBounds& BoundedEuclideanSpace::getBounds() const
{
  return bounds;
}

void BoundedEuclideanSpace::setBounds(const CoordinateBounds& new_bounds) 
{
  assert(new_bounds.getDimension() == getDimension());
  bounds = new_bounds;
}

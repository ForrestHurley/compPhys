
#include "bounded_euclidean_space.h"
#include <assert.h>

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(
  BoundedEuclideanSpace* space, const std::vector<double>& bounds) :
  EuclideanPoint(space), bounds(bounds)
{
  assert(getDimension() == bounds.size());  
}

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(
  BoundedEuclideanSpace* space,
  const std::vector<double>& bounds,
  const Coordinate& coordinate) :
  EuclideanPoint(space, coordinate), bounds(bounds)
{
  assert(bounds.size() == coordinate.dimension);
  assert(getDimension() == bounds.size());
}

void BoundedEuclideanSpace::BoundedEuclideanPoint::setCoordinate(const Coordinate& new_coordinate)
{
  Coordinate coordinate_bounds = Coordinate(bounds);
  Coordinate bounded_coordinate = new_coordinate.Clamp(Coordinate::Zero(getDimension()), coordinate_bounds);
  EuclideanPoint::setCoordinate(bounded_coordinate);
}

BoundedEuclideanSpace::BoundedEuclideanSpace(const std::vector<double>& bounds) :
  EuclideanSpace(bounds.size()), bounds(bounds),
  bounded_euclidean_origin(this, bounds) {}

BoundedEuclideanSpace::BoundedEuclideanSpace(const std::vector<double>& bounds,
  const Coordinate& zero_coordinate) :
  EuclideanSpace(zero_coordinate), bounds(bounds),
  bounded_euclidean_origin(this, bounds, zero_coordinate)
{
  assert(bounds.size() == zero_coordinate.dimension);
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

const std::vector<double>& BoundedEuclideanSpace::getBounds() const
{
  return bounds;
}

void BoundedEuclideanSpace::setBounds(const std::vector<double>& newBounds) 
{
  bounds = newBounds;
}

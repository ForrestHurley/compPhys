
#include "bounded_euclidean_space.h"
#include <assert.h>

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(const std::vector<double>& bounds) :
  EuclideanPoint(bounds.size()), bounds(bounds) {}

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(const std::vector<double>& bounds,
  const Coordinate& coordinate) :
  EuclideanPoint(coordinate), bounds(bounds)
{
  assert(bounds.size() == coordinate.dimension);
}

void BoundedEuclideanSpace::BoundedEuclideanPoint::setCoordinate(const Coordinate& new_coordinate)
{
  Coordinate coordinate_bounds(bounds);
  Coordinate bounded_coordinate = 
    ( ( (new_coordinate % coordinate_bounds) + coordinate_bounds) % coordinate_bounds);
  EuclideanPoint::setCoordinate(bounded_coordinate);
}

BoundedEuclideanSpace::BoundedEuclideanSpace(const std::vector<double>& bounds) :
  EuclideanSpace(bounds.size()), bounds(bounds),
  bounded_euclidean_origin(bounds) {}

BoundedEuclideanSpace::BoundedEuclideanSpace(const std::vector<double>& bounds,
  const Coordinate& zero_coordinate) :
  EuclideanSpace(zero_coordinate), bounds(bounds),
  bounded_euclidean_origin(bounds, zero_coordinate)
{
  assert(bounds.size() == zero_coordinate.dimension);
}

const BoundedEuclideanSpace::BoundedEuclideanPoint& BoundedEuclideanSpace::getOrigin() const
{
  return bounded_euclidean_origin;
}

const std::vector<double>& BoundedEuclideanSpace::getBounds() const
{
  return bounds;
}

void BoundedEuclideanSpace::setBounds(const std::vector<double>& newBounds) 
{
  bounds = newBounds;
}

#include "coordinate_bounds.h"
#include <assert.h>

CoordinateBounds::CoordinateBounds(
  const Coordinate& upper_bound)
  : upper_bound(upper_bound),
  lower_bound(Coordinate::Zero(upper_bound.dimension)),
  dimension(upper_bound.dimension) {}

CoordinateBounds::CoordinateBounds(
  const Coordinate& lower_bound,
  const Coordinate& upper_bound)
  : lower_bound(lower_bound), upper_bound(upper_bound),
  dimension(lower_bound.dimension)
{
  assert(lower_bound.dimension == upper_bound.dimension);  
}

CoordinateBounds::CoordinateBounds(
  const std::vector<double>& upper_bound)
  : upper_bound(upper_bound),
  lower_bound(Coordinate::Zero(upper_bound.size())),
  dimension(upper_bound.size()) {}

CoordinateBounds::CoordinateBounds(
  const std::vector<double>& lower_bound,
  const std::vector<double>& upper_bound)
  : lower_bound(lower_bound), upper_bound(upper_bound),
  dimension(lower_bound.size())
{
  assert(lower_bound.size() == upper_bound.size());
}

CoordinateBounds::CoordinateBounds(
  const CoordinateBounds& bounds) :
  lower_bound(bounds.lower_bound),
  upper_bound(bounds.upper_bound),
  dimension(bounds.getDimension()) {}

Coordinate CoordinateBounds::getRange() const
{
  return upper_bound - lower_bound;
}

const Coordinate& CoordinateBounds::getLowerBound() const
{
  return lower_bound;
}

const Coordinate& CoordinateBounds::getUpperBound() const
{
  return upper_bound;
}

void CoordinateBounds::setLowerBound(
  const Coordinate& bound)
{
  assert(bound.dimension == dimension);
  lower_bound = bound;
}

void CoordinateBounds::setUpperBound(
  const Coordinate& bound)
{
  assert(bound.dimension == dimension);
  upper_bound = bound;
}

void CoordinateBounds::setLowerUpperBound(
  const Coordinate& lower_bound,
  const Coordinate& upper_bound)
{
  assert(lower_bound.dimension == dimension);
  assert(upper_bound.dimension == dimension);
  this->lower_bound = lower_bound;
  this->upper_bound = upper_bound;
}

CoordinateBounds& CoordinateBounds::operator=(const CoordinateBounds& bounds)
{
  if (this == &bounds)
    return *this;
  assert(bounds.dimension == dimension);

  lower_bound = bounds.lower_bound;
  upper_bound = bounds.upper_bound;

  return *this;
}

int CoordinateBounds::getDimension() const
{
  return dimension;
}

Coordinate CoordinateBounds::ClampCoordinate(const Coordinate& coordinate) const
{
  assert(coordinate.dimension == dimension);
  Coordinate out = coordinate
    .Clamp(lower_bound, upper_bound);
  return out;
}

Coordinate CoordinateBounds::ModCoordinate(const Coordinate& coordinate) const
{
  assert(coordinate.dimension == dimension);
  const Coordinate range = getRange();
  Coordinate out = 
    ( ( (coordinate - lower_bound) % range )
    + range) % range + lower_bound;
  return out;
}

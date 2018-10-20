
#include "flat_torus_space.h"
#include <algorithm>

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(
  FlatTorusSpace* space,
  const std::vector<double>& bounds) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(space, bounds) {}

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(
  FlatTorusSpace* space,
  const std::vector<double>& bounds,
  const Coordinate& coordinate) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(space, bounds, coordinate) {}

void FlatTorusSpace::FlatTorusPoint::setCoordinate(const Coordinate& new_coordinate)
{
  Coordinate coordinate_bounds = Coordinate(bounds);
  Coordinate bounded_coordinate = 
    ( ( (new_coordinate % coordinate_bounds) + coordinate_bounds) % coordinate_bounds);
  EuclideanPoint::setCoordinate(bounded_coordinate);
}

FlatTorusSpace::FlatTorusSpace(const std::vector<double>& bounds) :
  BoundedEuclideanSpace(bounds), flat_torus_origin(this, bounds) {}

FlatTorusSpace::FlatTorusSpace(const std::vector<double>& bounds,
  const Coordinate& zero_coordinate) :
  BoundedEuclideanSpace(bounds, zero_coordinate),
  flat_torus_origin(this, bounds, zero_coordinate) {}

const FlatTorusSpace::FlatTorusPoint& FlatTorusSpace::getOrigin() const
{
  return flat_torus_origin;
}

FlatTorusSpace::FlatTorusPoint& FlatTorusSpace::CreatePoint(
  const Coordinate& coordinate)
{
  FlatTorusPoint* point = new FlatTorusPoint(this, bounds, coordinate);
  addPoint(point);
  return *point;
}

Coordinate FlatTorusSpace::DisplacementVector(
  const SmoothCoordinatePoint& A, const SmoothCoordinatePoint& B) const
{
  const FlatTorusPoint& a_torus = 
    dynamic_cast<const FlatTorusPoint&>(A);
  const FlatTorusPoint& b_torus = 
    dynamic_cast<const FlatTorusPoint&>(B);

  Coordinate difference_vector = b_torus.getCoordinate() - a_torus.getCoordinate();
  Coordinate alternative_difference = Coordinate(bounds) - difference_vector;
  double c = std::min<double>(1, 2);
  Coordinate minimum_differences = 
    difference_vector.ApplyFunction(
      static_cast<const double& (*) (const double&, const double&)>(std::min<double>),
      alternative_difference);

  return minimum_differences;
}


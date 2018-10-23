
#include "flat_torus_space.h"
#include <algorithm>
#include <iostream>

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(
  FlatTorusSpace* space,
  const CoordinateBounds& bounds) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(space, bounds) {}

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(
  FlatTorusSpace* space,
  const CoordinateBounds& bounds,
  const Coordinate& coordinate) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(space, bounds, 
    bounds.ModCoordinate(coordinate)) {}

void FlatTorusSpace::FlatTorusPoint::setCoordinate(const Coordinate& new_coordinate)
{
  EuclideanPoint::setCoordinate(
    bounds.ModCoordinate(new_coordinate));
}

FlatTorusSpace::FlatTorusSpace(const CoordinateBounds& bounds) :
  BoundedEuclideanSpace(bounds), flat_torus_origin(this, bounds) {}

FlatTorusSpace::FlatTorusSpace(const CoordinateBounds& bounds,
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
  assert(A.getSpace() == this);
  assert(B.getSpace() == this);
  const FlatTorusPoint& a_torus = 
    dynamic_cast<const FlatTorusPoint&>(A);
  const FlatTorusPoint& b_torus = 
    dynamic_cast<const FlatTorusPoint&>(B);

  Coordinate difference = 
    a_torus.getCoordinate() - b_torus.getCoordinate();
  std::vector<double> difference_vector = 
    difference.asVector();
  std::vector<double> alternative_difference = 
    (difference - difference.Sign() * bounds.getRange())
    .asVector();

  for (int i = 0; i < getDimension(); i++)
  {
    if (abs(difference_vector.at(i)) >
      abs(alternative_difference.at(i)))
      difference_vector.at(i) =
        alternative_difference.at(i);
  }
  Coordinate minimum_differences = 
    Coordinate(difference_vector);

  //std::cout << a_torus.getCoordinate() << " : " << b_torus.getCoordinate() << " : ";
  //std::cout << minimum_differences << std::endl;

  return minimum_differences;
}



#include "flat_torus_space.h"
#include <algorithm>

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(const std::vector<double>& bounds) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(bounds) {}

FlatTorusSpace::FlatTorusPoint::FlatTorusPoint(const std::vector<double>& bounds,
  const Coordinate& coordinate) :
  BoundedEuclideanSpace::BoundedEuclideanPoint(bounds, coordinate) {}

FlatTorusSpace::FlatTorusSpace(const std::vector<double>& bounds) :
  BoundedEuclideanSpace(bounds), flat_torus_origin(bounds) {}

FlatTorusSpace::FlatTorusSpace(const std::vector<double>& bounds,
  const Coordinate& zero_coordinate) :
  BoundedEuclideanSpace(bounds, zero_coordinate), flat_torus_origin(bounds, zero_coordinate){}

const FlatTorusSpace::FlatTorusPoint& FlatTorusSpace::getOrigin() const
{
  return flat_torus_origin;
}

double FlatTorusSpace::Distance(const MetricPoint& A, const MetricPoint& B) const
{
  const FlatTorusPoint& a_torus = 
    dynamic_cast<const FlatTorusPoint&>(A);
  const FlatTorusPoint& b_torus = 
    dynamic_cast<const FlatTorusPoint&>(B);

  Coordinate difference_vector = b_torus - a_torus;
  Coordinate alternative_difference = Coordinate(bounds) - difference_vector;
  Coordinate minimum_differences = 
    difference_vector.ApplyFunction(&std::min, alternative_difference);

  return minimum_differences.getMagnitude();
}


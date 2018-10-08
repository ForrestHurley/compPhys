
#include "bounded_euclidean_space.h"

BoundedEuclideanSpace::BoundedEuclideanPoint::BoundedEuclideanPoint(const std::vector<double>& bounds) :
  EuclideanPoint(bounds.size()), bounds(bounds) {}

void BoundedEuclideanSpace::BoundedEuclideanPoint::setCoordinate(const Coordinate& newCoordinate) {}

BoundedEuclideanSpace::BoundedEuclideanSpace(std::vector<double> bounds) :
  EuclideanSpace(bounds.size()), bounds(bounds), bounded_euclidean_origin(bounds) {}

const BoundedEuclideanSpace::BoundedEuclideanPoint& BoundedEuclideanSpace::getOrigin() const
{
  return bounded_euclidean_origin;
}

std::vector<double> BoundedEuclideanSpace::getBounds()
{
  return std::vector<double>();
}

void BoundedEuclideanSpace::setBounds(std::vector<double> newBounds) {};


#include "euclidean_space.h"

EuclideanSpace::EuclideanPoint::EuclideanPoint(unsigned int dimension) :
    dimension(dimension), coordinate(dimension) {}

Coordinate EuclideanSpace::EuclideanPoint::getCoordinate()
{
  return Coordinate(dimension);
}

void EuclideanSpace::EuclideanPoint::setCoordinate(const Coordinate& newCoordinate) {}

EuclideanSpace::EuclideanSpace(unsigned int dimension) : dimension(dimension), euclidean_origin(dimension) {}

double EuclideanSpace::Distance(const MetricPoint& A, const MetricPoint& B)
{
  return 0.;
}

double EuclideanSpace::Distance(const EuclideanSpace::EuclideanPoint& A,
                                const EuclideanSpace::EuclideanPoint& B)
{
  return 0.;
}

const EuclideanSpace::EuclideanPoint& EuclideanSpace::getOrigin()
{
  return euclidean_origin;
}

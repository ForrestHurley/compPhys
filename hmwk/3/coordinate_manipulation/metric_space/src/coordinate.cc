
#include "coordinate.h"

Coordinate::Coordinate(unsigned int dimension) : dimension(dimension) {};

Coordinate Coordinate::operator+(const Coordinate& other)
{
  return Coordinate(dimension);
}

Coordinate Coordinate::operator-(const Coordinate& other)
{
  return Coordinate(dimension);
}

Coordinate Coordinate::operator*(double other)
{
  return Coordinate(dimension);
}

Coordinate Coordinate::operator/(double other)
{
  return Coordinate(dimension);
}

double Coordinate::dot(const Coordinate& other)
{
  return 0;
}

Coordinate Coordinate::cross(const Coordinate& other)
{
  return Coordinate(dimension);
}

double Coordinate::getMagnitude()
{
  return 0;
}

double Coordinate::getMagnitudeSquared()
{
  return 0;
}

Coordinate Coordinate::getNormalized()
{
  return Coordinate(dimension);
}

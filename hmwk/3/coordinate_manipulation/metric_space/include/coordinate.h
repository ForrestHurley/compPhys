#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

class Coordinate
{
private:
  std::vector<double> values;

public:
  const unsigned int dimension;

  Coordinate(unsigned int dimension);

  Coordinate operator+(const Coordinate& other);
  Coordinate operator-(const Coordinate& other);
  Coordinate operator*(double other);
  Coordinate operator/(double other);

  double dot(const Coordinate& other);
  Coordinate cross(const Coordinate& other);

  double getMagnitude();
  double getMagnitudeSquared();

  Coordinate getNormalized();
};

#endif

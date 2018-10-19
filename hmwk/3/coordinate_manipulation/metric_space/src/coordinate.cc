
#include "coordinate.h"
#include <assert.h>
#include <limits>
#include <random>

Coordinate::Coordinate(unsigned int dimension) : dimension(dimension) {}

Coordinate::Coordinate(const std::vector<double>& values) : values(values), dimension(values.size()) {}

Coordinate Coordinate::Zero(unsigned int dimension) const
{
  std::vector<double> zero_vector(dimension, 0.);
  return zero_vector;
}

Coordinate Coordinate::ForwardUnit(unsigned int dimension) const
{
  assert(dimension >= 1);
  std::vector<double> unit_vector(dimension, 0.);
  unit_vector.at(0) = 1.;

  return Coordinate(unit_vector);
}

Coordinate Coordinate::INF(unsigned int dimension) const
{
  std::vector<double> inf_values(dimension, std::numeric_limits<double>::infinity());

  return Coordinate(inf_values);
}

Coordinate Coordinate::operator+(const Coordinate& other)
{
  assert(other.dimension == dimension);

  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) += other.values.at(i);

  return Coordinate(new_values);
}

Coordinate Coordinate::operator-(const Coordinate& other)
{
  assert(other.dimension == dimension);

  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) -= other.values.at(i);

  return Coordinate(new_values);
}

Coordinate Coordinate::operator*(const Coordinate& other)
{
  assert(other.dimension == dimension);

  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) *= other.values.at(i);

  return Coordinate(new_values);
}

Coordinate Coordinate::operator/(const Coordinate& other)
{
  assert(other.dimension == dimension);

  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) /= other.values.at(i);

  return Coordinate(new_values);
}

Coordinate Coordinate::operator%(const Coordinate& other)
{
  assert(other.dimension == dimension);

  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) %= other.values.at(i);

  return Coordinate(new_values);
}

Coordinate Coordinate::operator+(double other)
{
  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) += other;

  return Coordinate(new_values);
}

Coordinate Coordinate::operator-(double other)
{
  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) -= other;

  return Coordinate(new_values);
}

Coordinate Coordinate::operator*(double other)
{
  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) *= other;

  return Coordinate(new_values);
}

Coordinate Coordinate::operator/(double other)
{
  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) /= other;

  return Coordinate(new_values);
}

Coordinate Coordinate::operator%(double other)
{
  std::vector<double> new_values = values;
  for (int i = 0; i < dimension; i++)
    new_values.at(i) %= other;

  return Coordinate(new_values);
}

double Coordinate::dot(const Coordinate& other)
{
  assert(other.dimension == dimension);

  double dot_product = 0.;
  for (int i = 0; i < dimension; i++)
    dot_product += values.at(i) * other.values.at(i);

  return dot_product;
}

Coordinate Coordinate::cross(const Coordinate& other)
{
  assert(dimension == 3);
  assert(other.dimension == 3);

  double i, j, k;
  i = values.at(1) * other.values.at(2) - values.at(2) * other.values.at(1);
  j = values.at(2) * other.values.at(0) - values.at(0) * other.values.at(2);
  k = values.at(0) * other.values.at(1) - values.at(1) * other.values.at(0);

  std::vector<double> cross_product{i, j, k};

  return Coordinate(cross_product);
}

double Coordinate::getMagnitude()
{
  return sqrt(getMagnitudeSquared());
}

double Coordinate::getMagnitudeSquared()
{
  double magnitude_squared = 0;

  for (int i = 0; i < dimension; i++)
    magnitude_squared += values.at(i) * values.at(i);

  return magnitude_squared;
}

Coordinate Coordinate::getNormalized()
{
  double magnitude = getMagnitude();
  if (magnitude < 1e-10)
    return INF(dimension);

  Coordinate out = *this / magnitude;
  return out;
}

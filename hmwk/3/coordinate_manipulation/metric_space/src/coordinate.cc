
#include "coordinate.h"
#include <assert.h>
#include <limits>
#include <random>
#include <cmath>
#include <algorithm>

Coordinate::Coordinate(unsigned int dimension) : dimension(dimension)
{
  ResetCalculatedProperties();
}

Coordinate::Coordinate(const std::vector<double>& values) : values(values), dimension(values.size())
{
  ResetCalculatedProperties();
}

void Coordinate::ResetCalculatedProperties()
{
  magnitude = sqrt(getMagnitudeSquared());

  magnitude_squared = 0;

  for (int i = 0; i < dimension; i++)
    magnitude_squared += values.at(i) * values.at(i);
}

Coordinate Coordinate::Zero(unsigned int dimension)
{
  std::vector<double> zero_vector(dimension, 0.);
  return zero_vector;
}

Coordinate Coordinate::ForwardUnit(unsigned int dimension)
{
  assert(dimension >= 1);
  std::vector<double> unit_vector(dimension, 0.);
  unit_vector.at(0) = 1.;

  return Coordinate(unit_vector);
}

Coordinate Coordinate::INF(unsigned int dimension)
{
  std::vector<double> inf_values(dimension, std::numeric_limits<double>::infinity());

  return Coordinate(inf_values);
}

Coordinate& Coordinate::operator=(const Coordinate& coordinate)
{
  if (this == &coordinate)
    return *this;
  assert(coordinate.dimension == dimension);

  values = coordinate.values;
  magnitude = coordinate.magnitude;
  magnitude_squared = coordinate.magnitude_squared;

  return *this;
}

Coordinate& Coordinate::operator+=(const Coordinate& other)
{
  assert(other.dimension == dimension);

  for (int i = 0; i < dimension; i++)
    values.at(i) += other.values.at(i);

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator-=(const Coordinate& other)
{
  assert(other.dimension == dimension);

  for (int i = 0; i < dimension; i++)
    values.at(i) -= other.values.at(i);

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator*=(const Coordinate& other)
{
  assert(other.dimension == dimension);

  for (int i = 0; i < dimension; i++)
    values.at(i) *= other.values.at(i);

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator/=(const Coordinate& other)
{
  assert(other.dimension == dimension);

  for (int i = 0; i < dimension; i++)
    values.at(i) /= other.values.at(i);

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator%=(const Coordinate& other)
{
  assert(other.dimension == dimension);

  for (int i = 0; i < dimension; i++)
    values.at(i) =
      std::fmod(values.at(i), other.values.at(i));

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator+=(double other)
{
  for (int i = 0; i < dimension; i++)
    values.at(i) += other;

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator-=(double other)
{
  for (int i = 0; i < dimension; i++)
    values.at(i) -= other;

  ResetCalculatedProperties();

  return *this;
}

Coordinate& Coordinate::operator*=(double other)
{
  for (int i = 0; i < dimension; i++)
    values.at(i) *= other;

  magnitude *= other;
  magnitude_squared *= (other * other);

  return *this;
}

Coordinate& Coordinate::operator/=(double other)
{
  for (int i = 0; i < dimension; i++)
    values.at(i) /= other;

  magnitude /= other;
  magnitude_squared /= (other * other);

  return *this;
}

Coordinate& Coordinate::operator%=(double other)
{
  for (int i = 0; i < dimension; i++)
    values.at(i) =
      std::fmod(values.at(i), other);

  ResetCalculatedProperties();

  return *this;
}

Coordinate Coordinate::operator+(const Coordinate& other) const
{
  Coordinate out = *this;
  out += other;
  return out;
}

Coordinate Coordinate::operator-(const Coordinate& other) const
{
  Coordinate out = *this;
  out -= other;
  return out;
}

Coordinate Coordinate::operator*(const Coordinate& other) const
{
  Coordinate out = *this;
  out *= other;
  return out;
}

Coordinate Coordinate::operator/(const Coordinate& other) const
{
  Coordinate out = *this;
  out /= other;
  return out;
}

Coordinate Coordinate::operator%(const Coordinate& other) const
{
  Coordinate out = *this;
  out %= other;
  return out;
}

Coordinate Coordinate::operator+(double other) const
{
  Coordinate out = *this;
  out += other;
  return out;
}

Coordinate Coordinate::operator-(double other) const
{
  Coordinate out = *this;
  out -= other;
  return out;
}

Coordinate Coordinate::operator*(double other) const
{
  Coordinate out = *this;
  out *= other;
  return out;
}

Coordinate Coordinate::operator/(double other) const
{
  Coordinate out = *this;
  out /= other;
  return out;
}

Coordinate Coordinate::operator%(double other) const
{
  Coordinate out = *this;
  out %= other;
  return out;
}

bool Coordinate::operator>(const Coordinate& other) const
{
  assert(other.dimension == dimension);
  return values > other.values;
}

bool Coordinate::operator>=(const Coordinate& other) const
{
  assert(other.dimension == dimension);
  return values >= other.values;
}

bool Coordinate::operator==(const Coordinate& other) const
{
  assert(other.dimension == dimension);
  return values == other.values;
}

bool Coordinate::operator<=(const Coordinate& other) const
{
  assert(other.dimension == dimension);
  return values <= other.values;
}

bool Coordinate::operator<(const Coordinate& other) const
{
  assert(other.dimension == dimension);
  return values < other.values;
}

Coordinate Coordinate::Clamp(const Coordinate& min, const Coordinate& max) const
{
  assert(dimension == min.dimension);
  assert(dimension == max.dimension);

  Coordinate out = *this;

  for (int i = 0; i < dimension; i++)
    out.values.at(i) = 
      std::min(
        std::max(out.values.at(i),
          min.values.at(i)),
        max.values.at(i));

  return out;
}

Coordinate Coordinate::Abs() const
{
  Coordinate out = *this;
  for (int i = 0; i < out.values.size(); i++)
    out.values.at(i) = abs(out.values.at(i));
  return out;
}

Coordinate Coordinate::Sign() const
{
  Coordinate out = *this;
  for (int i = 0; i < out.values.size(); i++)
    out.values.at(i) =
      (0 < out.values.at(i)) - (out.values.at(i) < 0);
  return out;
}

double Coordinate::dot(const Coordinate& other) const
{
  assert(other.dimension == dimension);

  double dot_product = 0.;
  for (int i = 0; i < dimension; i++)
    dot_product += values.at(i) * other.values.at(i);

  return dot_product;
}

Coordinate Coordinate::cross(const Coordinate& other) const
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

double Coordinate::getMagnitude() const
{
  return magnitude;
}

double Coordinate::getMagnitudeSquared() const
{
  return magnitude_squared;
}

Coordinate Coordinate::getNormalized() const
{
  double magnitude = getMagnitude();
  if (magnitude < 1e-10)
    return INF(dimension);

  Coordinate out = *this;
  out /= magnitude;
  return out;
}

const std::vector<double>& Coordinate::asVector() const
{
  return values;
}

std::ostream& operator<<(
  std::ostream &os, const Coordinate& coordinate)
{
  if (coordinate.values.size() <= 0)
    return os;

  for (int i = 0; i < coordinate.values.size() - 1; i++) 
  {
    os << coordinate.values.at(i);
    os << ", ";
  }
  os << coordinate.values.at(
    coordinate.values.size() - 1);
  return os;
}

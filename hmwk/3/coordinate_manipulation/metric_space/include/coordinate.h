#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>
#include <random>
#include <assert.h>

class Coordinate
{
private:
  std::vector<double> values;

public:
  const unsigned int dimension;

  Coordinate(unsigned int dimension);
  Coordinate(const std::vector<double>& values);

  static Coordinate Zero(unsigned int dimension);
  static Coordinate ForwardUnit(unsigned int dimension);
  static Coordinate INF(unsigned int dimension);

  template< class RNG >
  static Coordinate RandomUnit(unsigned int dimension, RNG& generator)
  {
    std::vector<double> random_vector;
    random_vector.reserve(dimension);

    std::normal_distribution<double> distribution(0., 1.);

    for (int i = 0; i < dimension; i++)
      random_vector.push_back(distribution(generator));

    return Coordinate(random_vector).getNormalized();
  }

  Coordinate& operator=(const Coordinate&coordinate);

  Coordinate operator+(const Coordinate& other) const;
  Coordinate operator-(const Coordinate& other) const;
  Coordinate operator*(const Coordinate& other) const;
  Coordinate operator/(const Coordinate& other) const;
  Coordinate operator%(const Coordinate& other) const;
  Coordinate operator+(double other) const;
  Coordinate operator-(double other) const;
  Coordinate operator*(double other) const;
  Coordinate operator/(double other) const;
  Coordinate operator%(double other) const;

  double dot(const Coordinate& other) const;
  Coordinate cross(const Coordinate& other) const;

  double getMagnitude() const;
  double getMagnitudeSquared() const;

  template< typename Func >
  Coordinate ApplyFunction(const Func& foo) const
  {
    std::vector<double> out;
    out.reserve(dimension);

    for (int i = 0; i < dimension; i++)
      out.push_back(foo(values.at(i)));

    return out;
  }

  template< typename Func >
  Coordinate ApplyFunction(const Func& foo, const Coordinate& other) const
  {
    assert(dimension == other.dimension);
    std::vector<double> out;
    out.reserve(dimension);

    for (int i = 0; i < dimension; i++)
      out.push_back(foo(values.at(i), other.values.at(i)));

    return out;
  }

  Coordinate getNormalized() const;

  const std::vector<double>& asVector() const;
};

#endif

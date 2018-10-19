#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>
#include <random>

class Coordinate
{
private:
  std::vector<double> values;

public:
  const unsigned int dimension;

  Coordinate(unsigned int dimension);
  Coordinate(const std::vector<double>& values);

  static Coordinate Zero(unsigned int dimesnion) const;
  static Coordinate ForwardUnit(unsigned int dimension) const;
  static Coordinate INF(unsigned int dimension) const;

  template< class RNG >
  static Coordinate RandomUnit(unsigned int dimension, RNG& generator) const
  {
    std::vector<double> random_vector;
    random_vector.reserve(dimension);

    std::normal_distribution<double> distribution(0., 1.);

    for (int i = 0; i < dimension; i++)
      random_vector.push_back(distribution(generator));

    return Coordinate(random_vector).getNormalized();
  }

  Coordinate operator+(const Coordinate& other);
  Coordinate operator-(const Coordinate& other);
  Coordinate operator*(const Coordinate& other);
  Coordinate operator/(const Coordinate& other);
  Coordinate operator%(const Coordinate& other);
  Coordinate operator+(double other);
  Coordinate operator-(double other);
  Coordinate operator*(double other);
  Coordinate operator/(double other);
  Coordinate operator%(double other);

  double dot(const Coordinate& other);
  Coordinate cross(const Coordinate& other);

  double getMagnitude();
  double getMagnitudeSquared();

  template< typename Func >
  Coordinate ApplyFunction(Func foo)
  {
    std::vector<double> out;
    out.reserve(dimension);

    for (int i = 0; i < dimension; i++)
      out.push_back(foo(values.at(i)));

    return out;
  }

  template< typename Func >
  Coordinate ApplyFunction(Func foo, const Coordinate& other)
  {
    assert(dimension == other.dimension)
    std::vector<double> out;
    out.reserve(dimension);

    for (int i = 0; i < dimension; i++)
      out.push_back(foo(values.at(i), other.values.at(i)));

    return out;
  }

  Coordinate getNormalized();
};

#endif

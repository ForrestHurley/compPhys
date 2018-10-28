#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>
#include <random>
#include <assert.h>
#include <iostream>

class Coordinate
{
private:
  std::vector<double> values;
  mutable double magnitude_squared;
  mutable double magnitude;

  void ResetCalculatedProperties();

public:
  const unsigned int dimension;

  Coordinate(unsigned int dimension);
  Coordinate(const std::vector<double>& values);

  static Coordinate Zero(unsigned int dimension);
  static Coordinate ForwardUnit(unsigned int dimension);
  static Coordinate INF(unsigned int dimension);

  template< class RNG >
  static Coordinate RandomGaussian(unsigned int dimension, RNG& generator)
  {
    std::vector<double> random_vector;
    random_vector.reserve(dimension);

    std::normal_distribution<double> distribution(0., 1.);
    const double recip_dimension = 1. / dimension; //For normalizing the expected value of x^2

    for (int i = 0; i < dimension; i++)
      random_vector.push_back(distribution(generator) * recip_dimension);

    return Coordinate(random_vector);
  }

  template< class RNG >
  static Coordinate RandomUnit(unsigned int dimension, RNG& generator)
  {
    return RandomGaussian(dimension, generator).getNormalized();
  }

  template< class RNG >
  static Coordinate RandomUniform(unsigned int dimension, RNG& generator)
  {
    std::vector<double> random_vector;
    random_vector.reserve(dimension);

    std::uniform_real_distribution<double> distribution(0., 1.);

    for (int i = 0; i < dimension; i++)
      random_vector.push_back(distribution(generator));

    return Coordinate(random_vector);
  }

  Coordinate& operator=(const Coordinate&coordinate);

  Coordinate& operator+=(const Coordinate& other);
  Coordinate& operator-=(const Coordinate& other);
  Coordinate& operator*=(const Coordinate& other);
  Coordinate& operator/=(const Coordinate& other);
  Coordinate& operator%=(const Coordinate& other);
  Coordinate& operator+=(double other);
  Coordinate& operator-=(double other);
  Coordinate& operator*=(double other);
  Coordinate& operator/=(double other);
  Coordinate& operator%=(double other);
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
  bool operator>(const Coordinate& other) const;
  bool operator>=(const Coordinate& other) const;
  bool operator==(const Coordinate& other) const;
  bool operator<=(const Coordinate& other) const;
  bool operator<(const Coordinate& other) const;

  Coordinate Clamp(const Coordinate& min, const Coordinate& max) const;
  Coordinate Abs() const;
  Coordinate Sign() const;

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

  friend std::ostream& operator<<(std::ostream &os, 
    const Coordinate& coordinate);
};

#endif

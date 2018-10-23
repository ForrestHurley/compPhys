#ifndef COORDINATE_BOUNDS_H
#define COORDINATE_BOUNDS_H

#include "coordinate.h"
#include <vector>

class CoordinateBounds
{
private:
  Coordinate lower_bound;
  Coordinate upper_bound;

  const int dimension;

public:
  explicit CoordinateBounds(
    const Coordinate& upper_bound);
  CoordinateBounds(
    const Coordinate& lower_bound,
    const Coordinate& upper_bound);
  explicit CoordinateBounds(
    const std::vector<double>& upper_bound);
  CoordinateBounds(
    const std::vector<double>& lower_bound,
    const std::vector<double>& upper_bound);
  CoordinateBounds(
    const CoordinateBounds& bounds);

  Coordinate getRange() const;
  const Coordinate& getLowerBound() const;
  const Coordinate& getUpperBound() const;
  void setLowerBound(const Coordinate& bound);
  void setUpperBound(const Coordinate& bound);
  void setLowerUpperBound(
    const Coordinate& lower_bound,
    const Coordinate& upper_bound);

  CoordinateBounds& operator=(const CoordinateBounds& bounds);

  int getDimension() const;

  Coordinate ClampCoordinate(const Coordinate& coordinate) const;
  Coordinate ModCoordinate(const Coordinate& coordinate) const;
};

#endif

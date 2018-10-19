#ifndef FLAT_TORUS_SPACE_H
#define FLAT_TORUS_SPACE_H

#include "bounded_euclidean_space.h"

class FlatTorusSpace : public BoundedEuclideanSpace
{
public:
  class FlatTorusPoint : public BoundedEuclideanSpace::BoundedEuclideanPoint
  {
  public:
    FlatTorusPoint(const std::vector<double>& bounds);
    FlatTorusPoint(const std::vector<double>& bounds,
      const Coordinate& coordinate);

    virtual void setCoordinate(const Coordinate& newCoordinate) override;
  };

private:
  const FlatTorusPoint flat_torus_origin;

public:
  FlatTorusSpace(const std::vector<double>& bounds);
  FlatTorusSpace(const std::vector<double>& bounds,
    const Coordinate& zero_coordinate);

  virtual const FlatTorusPoint& getOrigin() const override;

  virtual Coordinate DisplacementVector(
    const SmoothCoordinatePoint& A, const SmoothCoordinatePoint& B) const override;
};

#endif

#ifndef FLAT_TORUS_SPACE_H
#define FLAT_TORUS_SPACE_H

#include "bounded_euclidean_space.h"

class FlatTorusSpace : public BoundedEuclideanSpace
{
public:
  class FlatTorusPoint : public BoundedEuclideanSpace::BoundedEuclideanPoint
  {
  public:
    FlatTorusPoint(
      FlatTorusSpace* space,
      const CoordinateBounds& bounds);
    FlatTorusPoint(
      FlatTorusSpace* space,
      const CoordinateBounds& bounds,
      const Coordinate& coordinate);
    virtual ~FlatTorusPoint() {}

    virtual void setCoordinate(const Coordinate& new_coordinate) override;

    const FlatTorusSpace* getSpace() const
      { return static_cast<const FlatTorusSpace*>(MetricPoint::getSpace()); }
  };

private:
  const FlatTorusPoint flat_torus_origin;

public:
  FlatTorusSpace(const CoordinateBounds& bounds);
  FlatTorusSpace(const CoordinateBounds& bounds,
    const Coordinate& zero_coordinate);
  virtual ~FlatTorusSpace() {}

  virtual const FlatTorusPoint& getOrigin() const override;
  virtual FlatTorusPoint& CreatePoint(const Coordinate& coordinate) override;

  Coordinate DisplacementVector(
    const SmoothCoordinatePoint& A, const SmoothCoordinatePoint& B) const;
};

#endif

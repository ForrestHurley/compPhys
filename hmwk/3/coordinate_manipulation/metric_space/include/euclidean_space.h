#ifndef EUCLIDEAN_SPACE_H
#define EUCLIDEAN_SPACE_H

#include "smooth_coordinate_space.h"

class EuclideanSpace : public SmoothCoordinateSpace
{
public:
  class EuclideanPoint : public SmoothCoordinateSpace::SmoothCoordinatePoint
  {
  public:
    EuclideanPoint(EuclideanSpace* space);
    EuclideanPoint(EuclideanSpace* space, const Coordinate& coordinate);

    const EuclideanSpace* getSpace() const
      { return static_cast<const EuclideanSpace*>(MetricPoint::getSpace()); }
  };

private:
  const EuclideanPoint coordinate_origin;

public:
  EuclideanSpace(unsigned int dimension = 2);
  EuclideanSpace(const Coordinate& zero_coordinate);

  virtual double Distance(const MetricPoint& A, const MetricPoint& B) const override;
  virtual Coordinate DisplacementVector(
    const SmoothCoordinatePoint& A, const SmoothCoordinatePoint& B) const override;

  virtual const EuclideanPoint& getOrigin() const override;
};

#endif

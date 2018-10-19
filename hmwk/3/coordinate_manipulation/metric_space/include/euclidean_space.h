#ifndef EUCLIDEAN_SPACE_H
#define EUCLIDEAN_SPACE_H

#include "smooth_coordinate_space.h"

class EuclideanSpace : public SmoothCoordinateSpace
{
public:
  class EuclideanPoint : public SmoothCoordinateSpace::SmoothCoordinatePoint
  {
  public:
    EuclideanPoint(unsigned int dimension = 2);
    EuclideanPoint(const Coordinate& coordinate);
  };

private:
  const EuclideanPoint coordinate_origin;

public:
  EuclideanSpace(unsigned int dimension = 2);
  EuclideanSpace(const Coordinate& zero_coordinate);

  double Distance(const MetricPoint& A, const MetricPoint& B) const override;

  virtual const EuclideanPoint& getOrigin() const override;
};

#endif

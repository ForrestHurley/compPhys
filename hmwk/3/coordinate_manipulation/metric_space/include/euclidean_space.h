#ifndef EUCLIDEAN_SPACE_H
#define EUCLIDEAN_SPACE_H

#include "metric_space.h"
#include "coordinate.h"

class EuclideanSpace : public MetricSpace
{
public:
  class EuclideanPoint : public MetricSpace::MetricPoint
  {
  public:
    Coordinate coordinate;

    EuclideanPoint(unsigned int dimension = 2);
  };

private:
  EuclideanPoint euclidean_origin;

public:

  const unsigned int dimension;

  EuclideanSpace(unsigned int dimension = 2);

  double Distance(const MetricPoint& A, const MetricPoint& B) override;
  virtual double Distance(const EuclideanPoint& A, const EuclideanPoint& B);

  virtual EuclideanPoint& getOrigin() override;
};

#endif

#ifndef EUCLIDEAN_SPACE_H
#define EUCLIDEAN_SPACE_H

#include "metric_space.h"
#include "coordinate.h"

class EuclideanSpace : public MetricSpace
{
public:
  class EuclideanPoint : public MetricSpace::MetricPoint
  {
  protected:
    Coordinate coordinate;

  public:
    const unsigned int dimension;

    EuclideanPoint(unsigned int dimension = 2);

    Coordinate getCoordinate();
    virtual void setCoordinate(const Coordinate& newCoordinate);
  };

private:
  const EuclideanPoint euclidean_origin;

public:

  const unsigned int dimension;

  EuclideanSpace(unsigned int dimension = 2);

  double Distance(const MetricPoint& A, const MetricPoint& B) override;
  virtual double Distance(const EuclideanPoint& A, const EuclideanPoint& B);

  virtual const EuclideanPoint& getOrigin() override;
};

#endif

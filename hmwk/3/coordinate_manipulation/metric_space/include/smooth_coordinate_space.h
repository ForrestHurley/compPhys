#ifndef SMOOTH_COORDINATE_SPACE
#define SMOOTH_COORDINATE_SPACE

#include "metric_space.h"
#include "coordinate.h"

class SmoothCoordinateSpace : public MetricSpace
{
public:
  class SmoothCoordinatePoint : public MetricSpace::MetricPoint
  {
  protected:
    Coordinate coordinate;

  public:
    const unsigned int dimension;
    
    SmoothCoordinatePoint(unsigned int dimension = 2);

    Coordinate getCoordinate() const;
    virtual void setCoordinate(const Coordinate& newCoordinate);
  };

private:
  const SmoothCoordinatePoint coordinate_origin;

public:
  const unsigned int dimension;

  SmoothCoordinateSpace(unsigned int dimension = 2);

  virtual const SmoothCoordinatePoint& getOrigin() const override;
};

#endif

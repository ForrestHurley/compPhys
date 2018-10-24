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
    SmoothCoordinatePoint(SmoothCoordinateSpace* space);
    SmoothCoordinatePoint(SmoothCoordinateSpace* space, const Coordinate& coordinate);
    virtual ~SmoothCoordinatePoint() {}

    const Coordinate& getCoordinate() const;
    virtual void setCoordinate(const Coordinate& newCoordinate);

    int getDimension() const;

    const SmoothCoordinateSpace* getSpace() const
      { return static_cast<const SmoothCoordinateSpace*>(MetricPoint::getSpace()); }
  };

private:
  const unsigned int dimension;
  const SmoothCoordinatePoint coordinate_origin;

public:
  SmoothCoordinateSpace(unsigned int dimension = 2);
  SmoothCoordinateSpace(const Coordinate& zero_coordinate);
  virtual ~SmoothCoordinateSpace() {}

  virtual const SmoothCoordinatePoint& getOrigin() const override;
  virtual SmoothCoordinatePoint& CreatePoint(const Coordinate& coordinate);
  virtual void DestroyPoint(SmoothCoordinatePoint* point);

  virtual Coordinate DisplacementVector(
    const SmoothCoordinatePoint& A, const SmoothCoordinatePoint& B) const = 0;

  int getDimension() const { return dimension; }
};

#endif

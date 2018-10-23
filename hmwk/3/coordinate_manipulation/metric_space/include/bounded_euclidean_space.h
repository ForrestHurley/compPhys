#ifndef BOUNDED_EUCLIDEAN_SPACE_H
#define BOUNDED_EUCLIDEAN_SPACE_H

#include "euclidean_space.h"
#include "coordinate_bounds.h"

//TODO: Support minimum bounds other than 0
class BoundedEuclideanSpace : public EuclideanSpace
{
public:
  class BoundedEuclideanPoint : public EuclideanSpace::EuclideanPoint
  {
  protected:
    const CoordinateBounds& bounds;

  public:
    BoundedEuclideanPoint(
      BoundedEuclideanSpace* space,
      const CoordinateBounds& bounds);
    BoundedEuclideanPoint(
      BoundedEuclideanSpace* space,
      const CoordinateBounds& bounds,
      const Coordinate& coordinate);
    virtual ~BoundedEuclideanPoint() {}

    virtual void setCoordinate(const Coordinate& new_coordinate) override;

    const BoundedEuclideanSpace* getSpace() const
      { return static_cast<const BoundedEuclideanSpace*>(MetricPoint::getSpace()); }
  };

protected:
  CoordinateBounds bounds;

private:
  const BoundedEuclideanPoint bounded_euclidean_origin;

public:
  BoundedEuclideanSpace(const CoordinateBounds& bounds);
  BoundedEuclideanSpace(const CoordinateBounds& bounds,
    const Coordinate& zero_coordinate);
  virtual ~BoundedEuclideanSpace() {}

  virtual const BoundedEuclideanPoint& getOrigin() const override;
  virtual BoundedEuclideanPoint& CreatePoint(const Coordinate& coordinate) override;

  const CoordinateBounds& getBounds() const;
  void setBounds(const CoordinateBounds& newBounds);
};

#endif

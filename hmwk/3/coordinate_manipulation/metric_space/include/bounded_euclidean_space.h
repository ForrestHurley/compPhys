#ifndef BOUNDED_EUCLIDEAN_SPACE_H
#define BOUNDED_EUCLIDEAN_SPACE_H

#include "euclidean_space.h"
#include <vector>

class BoundedEuclideanSpace : public EuclideanSpace
{
public:
  class BoundedEuclideanPoint : public EuclideanSpace::EuclideanPoint
  {
  protected:
    const std::vector<double>& bounds;

  public:
    BoundedEuclideanPoint(
      BoundedEuclideanSpace* space,
      const std::vector<double>& bounds);
    BoundedEuclideanPoint(
      BoundedEuclideanSpace* space,
      const std::vector<double>& bounds,
      const Coordinate& coordinate);

    virtual void setCoordinate(const Coordinate& new_coordinate) override;

    const BoundedEuclideanSpace* getSpace() const
      { return static_cast<const BoundedEuclideanSpace*>(MetricPoint::getSpace()); }
  };

private:
  const BoundedEuclideanPoint bounded_euclidean_origin;

protected:
  std::vector<double> bounds;

public:
  BoundedEuclideanSpace(const std::vector<double>& bounds);
  BoundedEuclideanSpace(const std::vector<double>& bounds,
    const Coordinate& zero_coordinate);

  virtual const BoundedEuclideanPoint& getOrigin() const override;

  const std::vector<double>& getBounds() const;
  void setBounds(const std::vector<double>& newBounds);
};

#endif

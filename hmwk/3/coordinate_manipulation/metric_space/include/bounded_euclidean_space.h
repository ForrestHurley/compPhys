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
    BoundedEuclideanPoint(const std::vector<double>& bounds);

    virtual void setCoordinate(const Coordinate& newCoordinate) override;
  };

private:
  const BoundedEuclideanPoint bounded_euclidean_origin;

protected:
  std::vector<double> bounds;

public:
  BoundedEuclideanSpace(std::vector<double> bounds);

  virtual const BoundedEuclideanPoint& getOrigin() override;

  std::vector<double> getBounds();
  void setBounds(std::vector<double> newBounds);
};

#endif

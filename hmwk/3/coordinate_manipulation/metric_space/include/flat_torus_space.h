#ifndef FLAT_TORUS_SPACE_H
#define FLAT_TORUS_SPACE_H

#include "bounded_euclidean_space.h"

class FlatTorusSpace : public BoundedEuclideanSpace
{
public:
  class FlatTorusPoint : public BoundedEuclideanSpace::BoundedEuclideanPoint
  {
  public:
    FlatTorusPoint(const std::vector<double>& bounds);

    virtual void setCoordinate(const Coordinate& newCoordinate) override;
  };

private:
  const FlatTorusPoint flat_torus_origin;

public:
  FlatTorusSpace(std::vector<double> bounds);

  virtual const FlatTorusPoint& getOrigin() override;

  double Distance(const EuclideanPoint& A, const EuclideanPoint& B) override;
  virtual double Distance(const FlatTorusPoint& A, const FlatTorusPoint& B);
};

#endif

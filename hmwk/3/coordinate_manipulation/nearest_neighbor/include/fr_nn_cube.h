#ifndef FR_NN_CUBE_H
#define FR_NN_CUBE_H

#include "fixed_radius_nn.h"
#include <vector>
#include "euclidean_space.h"
#include "binned_coordinates.h"

class CubedFixedRadiusNearestNeighbor : public FixedRadiusNearestNeighbor
{
protected:
  int next_point_index;
  std::vector< std::vector<EuclideanSpace::EuclideanPoint*> > boxed_points;
  BinnedCoordinates coordinate_bins;

public:
  CubedFixedRadiusNearestNeighbor(const EuclideanSpace& metric,
    const std::vector<EuclideanSpace::EuclideanPoint*> points, double radius);

  virtual MetricSpace::MetricPoint* getNextNeighborSet(std::vector<MetricSpace::MetricPoint*>& neighboring_point_set) override; 
};

#endif

#ifndef FR_NN_CUBED_TORUS_H
#define FR_NN_CUBED_TORUS_H

#include "fr_nn_cube.h"
#include "flat_torus_space.h"

class CubedTorusFixedRadiusNearestNeighbor : public CubedFixedRadiusNearestNeighbor
{
public:
  CubedTorusFixedRadiusNearestNeighbor(
    const FlatTorusSpace& metric,
    const std::vector<FlatTorusSpace::FlatTorusPoint*> points,
    double radius,
    bool repeat_adjacencies = true);

  virtual MetricSpace::MetricPoint* getNextNeighborSet(std::vector<MetricSpace::MetricPoint*>& neighboring_point_set) override;
};

#endif

#ifndef FR_NN_BRUTE_H
#define FR_NN_BRUTE_H

#include "fixed_radius_nn.h"

class BruteForceFixedRadiusNearestNeighbor : public FixedRadiusNearestNeighbor
{
private:
  int next_point_index;

public:
  BruteForceFixedRadiusNearestNeighbor(
    const MetricSpace& metric,
    const std::vector<MetricSpace::MetricPoint*> points,
    double radius,
    bool repeat_adjacencies = true);

  MetricSpace::MetricPoint* getNextNeighborSet(std::vector<MetricSpace::MetricPoint*>& neighboring_point_set) override;
};

#endif

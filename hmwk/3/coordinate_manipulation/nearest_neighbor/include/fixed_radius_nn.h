#ifndef FIXED_RADIUS_NN_H
#define FIXED_RADIUS_NN_H

#include "metric_space.h"
#include <vector>

class FixedRadiusNearestNeighbor
{
public:
  const MetricSpace& metric;
  const std::vector<MetricSpace::MetricPoint*> points;
  const double radius;

  FixedRadiusNearestNeighbor(const MetricSpace& metric, const std::vector<MetricSpace::MetricPoint*> points, double radius);

  virtual MetricSpace::MetricPoint* getNextNeighborSet(std::vector<MetricSpace::MetricPoint*>& neighboring_point_set) = 0;
};

#endif

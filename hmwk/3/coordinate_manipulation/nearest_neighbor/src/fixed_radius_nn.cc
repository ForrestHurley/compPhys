
#include "fixed_radius_nn.h"

FixedRadiusNearestNeighbor::FixedRadiusNearestNeighbor(const MetricSpace& metric,
  const std::vector<MetricSpace::MetricPoint*> points, double radius) :
  metric(metric), points(points), radius(radius) {}

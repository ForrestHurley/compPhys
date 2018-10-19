
#include "fixed_radius_nn.h"

FixedRadiusNearestNeighbor::FixedRadiusNearestNeighbor(
  const MetricSpace& metric,
  const std::vector<MetricSpace::MetricPoint*> points,
  double radius,
  bool repeat_adjacencies) :
  metric(metric), points(points), radius(radius),
  repeat_adjacencies(repeat_adjacencies) {}

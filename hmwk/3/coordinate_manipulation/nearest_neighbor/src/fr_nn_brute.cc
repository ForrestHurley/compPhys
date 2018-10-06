
#include "fr_nn_brute.h"

BruteForceFixedRadiusNearestNeighbor::BruteForceFixedRadiusNearestNeighbor(const MetricSpace& metric,
  const std::vector<MetricSpace::MetricPoint*> points, double radius) :
  FixedRadiusNearestNeighbor(metric, points, radius) {}

MetricSpace::MetricPoint* BruteForceFixedRadiusNearestNeighbor::getNextNeighborSet(
  std::vector<MetricSpace::MetricPoint*>& neighboring_point_set)
{
  return points.at(0);
}

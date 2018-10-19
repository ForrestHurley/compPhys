
#include "fr_nn_brute.h"

BruteForceFixedRadiusNearestNeighbor::BruteForceFixedRadiusNearestNeighbor(
  const MetricSpace& metric,
  const std::vector<MetricSpace::MetricPoint*> points,
  double radius,
  bool repeat_adjacencies) :
  FixedRadiusNearestNeighbor(metric, points, radius, repeat_adjacencies),
  next_point_index(0) {}

MetricSpace::MetricPoint* BruteForceFixedRadiusNearestNeighbor::getNextNeighborSet(
  std::vector<MetricSpace::MetricPoint*>& neighboring_point_set)
{
  neighboring_point_set = std::vector<MetricSpace::MetricPoint*>();

  int i = 0;
  if (!repeat_adjacencies)
    i = next_point_index + 1;

  for (; i < points.size(); i++)
  {
    if (i == next_point_index)
      continue;

    if (metric.Distance(
      *points.at(next_point_index),
      *points.at(i)) < radius)
      neighboring_point_set.push_back(points.at(i));
  }
  return points.at(next_point_index++);
}

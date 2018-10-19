
#include "fr_nn_cubed_torus.h"

CubedTorusFixedRadiusNearestNeighbor::CubedTorusFixedRadiusNearestNeighbor(
  const FlatTorusSpace& metric,
  const std::vector<FlatTorusSpace::FlatTorusPoint*> points,
  double radius,
  bool repeat_adjacencies) :
  CubedFixedRadiusNearestNeighbor(metric, points, radius, repeat_adjacencies) {}

MetricSpace::MetricPoint* CubedTorusFixedRadiusNearestNeighbor::getNextNeighborSet(
  std::vector<MetricSpace::MetricPoint*>& neighboring_point_set)
{
  return points.at(0);
}

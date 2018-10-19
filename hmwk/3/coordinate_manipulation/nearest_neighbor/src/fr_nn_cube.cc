
#include "fr_nn_cube.h"

CubedFixedRadiusNearestNeighbor::CubedFixedRadiusNearestNeighbor(
  const EuclideanSpace& metric,
  const std::vector<EuclideanSpace::EuclideanPoint*> points,
  double radius,
  bool repeat_adjacencies) :
  FixedRadiusNearestNeighbor(
    metric,
    std::vector<MetricSpace::MetricPoint*>(points.begin(), points.end()),
    radius,
    repeat_adjacencies), 
  coordinate_bins(std::vector<int>()),
  next_point_index(0) {}

MetricSpace::MetricPoint* CubedFixedRadiusNearestNeighbor::getNextNeighborSet(
  std::vector<MetricSpace::MetricPoint*>& neighboring_point_set)
{
  return points.at(0);
}

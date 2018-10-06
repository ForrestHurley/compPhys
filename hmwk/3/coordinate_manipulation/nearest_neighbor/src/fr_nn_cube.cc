
#include "fr_nn_cube.h"

CubedFixedRadiusNearestNeighbor::CubedFixedRadiusNearestNeighbor(const EuclideanSpace& metric,
  const std::vector<EuclideanSpace::EuclideanPoint*> points, double radius) :
  FixedRadiusNearestNeighbor(metric,
  std::vector<MetricSpace::MetricPoint*>(points.begin(), points.end()), radius), 
  coordinate_bins(std::vector<int>()) {}

MetricSpace::MetricPoint* CubedFixedRadiusNearestNeighbor::getNextNeighborSet(
  std::vector<MetricSpace::MetricPoint*>& neighboring_point_set)
{
  return points.at(0);
}

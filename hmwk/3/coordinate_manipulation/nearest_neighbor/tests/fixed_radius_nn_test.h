#ifndef FIXED_RADIUS_NN_TEST_H
#define FIXED_RADIUS_NN_TEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "fixed_radius_nn.h"

class MockFixedRadiusNearestNeighbor : public FixedRadiusNearestNeighbor
{
public:
  MOCK_METHOD1(getNextNeighborSet, MetricSpace::MetricPoint* (std::vector<MetricSpace::MetricPoint*>& neighboring_point_set) );
};

#endif

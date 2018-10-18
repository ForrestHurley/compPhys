#ifndef ODE_INTERFACE_TEST_H
#define ODE_INTERFACE_TEST_H

#include "ode_interface.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class MockODEInterface : public ODEInterface
{
public:
  MockODEInterface(int degree) : ODEInterface(degree) {};

  using ODEInterface::CalculateHighestDerivative;
  MOCK_METHOD2(CalculateHighestDerivative, 
    std::vector<double> (const std::vector< std::vector<double> > &values, double time) );
};

#endif

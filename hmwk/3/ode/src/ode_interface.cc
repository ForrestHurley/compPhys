
#include "ode_interface.h"

ODEInterface::ODEInterface(int degree) : degree(degree) {}

std::vector<double> ODEInterface::CalculateHighestDerivative(const std::vector< std::vector<double> > &values, double time_step)
{
  return std::vector<double>();  
}

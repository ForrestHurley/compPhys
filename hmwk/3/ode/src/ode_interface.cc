
#include "ode_interface.h"

ODEInterface::ODEInterface(int degree) : degree(degree) {}

double ODEInterface::CalculateHighestDerivative(const std::vector<double> &values, double time)
{
  std::vector< std::vector<double> > manip_vect;
  manip_vect.push_back(values);

  return CalculateHighestDerivative(manip_vect, time).at(0);
}

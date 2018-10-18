#ifndef ODE_INTERFACE_H
#define ODE_INTERFACE_H

#include <vector>

class ODEInterface
{
public:
  const int degree;
  
  ODEInterface(int degree);

  virtual double CalculateHighestDerivative(const std::vector<double> &values, double time);
  virtual std::vector<double> CalculateHighestDerivative(const std::vector< std::vector<double> > &values, double time) = 0;
};

#endif

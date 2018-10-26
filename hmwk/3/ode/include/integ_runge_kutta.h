#ifndef INTEG_RUNGE_KUTTA_H
#define INTEG_RUNGE_KUTTA_H

#include "ode_solver.h"
#include "ode_interface.h"
#include <vector>

class RungeKuttaIntegrator : public ODESolver
{
private:
  std::vector< std::vector<double> > CalculateFullDerivative(std::vector< std::vector<double> > state, double time);

  void multiply(std::vector< std::vector<double> > &vect, double scalar);
  void add(std::vector< std::vector<double> > &A, const std::vector< std::vector<double> > &B);

protected:
  virtual void StepState(double time_step, double time = 0) override;

public:
  RungeKuttaIntegrator(bool flatten_input_state = false);
  RungeKuttaIntegrator(ODEInterface *differential_equation, bool flatten_input_state = false);
};

#endif

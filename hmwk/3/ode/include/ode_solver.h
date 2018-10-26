#ifndef ODE_SOLVER_H
#define ODE_SOLVER_H

#include <vector>
#include "ode_interface.h"

class ODESolver
{
protected:
  ODEInterface *differential_equation;
  bool flatten_input_state;

  std::vector< std::vector<double> > state;

  virtual void StepState(double time_step, double time = 0) = 0;

public:
  ODESolver(bool flatten_input_state = false);
  ODESolver(ODEInterface *differential_equation, bool flatten_input_state = false); 

  void setDifferentialEquation(ODEInterface *differential_equation);
  void setState(const std::vector< std::vector<double> > &state);
  void setState(const std::vector<double> &state);
  const std::vector< std::vector<double> >& getState() const;

  virtual void EvolveState(double total_time, int number_of_steps, double initial_time = 0); 
  
  bool getFlattenState() const { return flatten_input_state; }
};

#endif

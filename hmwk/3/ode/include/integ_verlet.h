#ifndef INTEG_VERLET_H
#define INTEG_VERLET_H

#include "ode_solver.h"
#include "ode_interface.h"
#include <vector>

class VerletIntegrator : public ODESolver
{
private:
  std::vector< std::vector<double> > previous_state;

  void InitializeFirstState(std::vector<double> &state,
    double time_step, double initial_time = 0);
  void InitializeFirstState(std::vector< std::vector<double> > &state,
    double time_step, double initial_time = 0);

protected:
  void StepState(
    std::vector< std::vector<double> > &state,
    double time_step, double time = 0) override;

  ODESolver& initial_solver;

public:
  VerletIntegrator();
  VerletIntegrator(ODEInterface *differential_equation);
  VerletIntegrator(ODEInterface *differential_equation, ODESolver& initial_solver);

  void setInitialSolver(ODESolver* initial_solver);

  virtual void EvolveState(
    std::vector< std::vector<double> > &state, double total_time,
    int number_of_steps, double initial_time = 0) override;
  virtual void EvolveState(
    std::vector<double> &state, double total_time,
    int number_of_steps, double initial_time = 0) override;
  
};

#endif

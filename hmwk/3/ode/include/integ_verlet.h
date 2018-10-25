#ifndef INTEG_VERLET_H
#define INTEG_VERLET_H

#include "ode_solver.h"
#include "ode_interface.h"
#include "smooth_coordinate_space.h"
#include <vector>

class VerletIntegrator : public ODESolver
{
private:
  std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >* 
    previous_state;
  SmoothCoordinateSpace* space;
  const bool owns_space;

  void InitializeFirstState(std::vector<double> &state,
    double time_step, double initial_time = 0);
  void InitializeFirstState(std::vector< std::vector<double> > &state,
    double time_step, double initial_time = 0);

  std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >*
    StateToPositions(const std::vector< std::vector<double> >& state);
  void DeletePoints(
    const std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >& points);

protected:
  void StepState(
    std::vector< std::vector<double> > &state,
    double time_step, double time = 0) override;

  ODESolver& initial_solver;

public:
  VerletIntegrator(unsigned int dimension = 2);
  VerletIntegrator(SmoothCoordinateSpace* space);
  VerletIntegrator(ODEInterface *differential_equation, unsigned int dimension = 2);
  VerletIntegrator(ODEInterface *differential_equation, SmoothCoordinateSpace* space);
  VerletIntegrator(ODEInterface *differential_equation, SmoothCoordinateSpace* space,
    ODESolver& initial_solver);

  void setInitialSolver(ODESolver* initial_solver);

  virtual void EvolveState(
    std::vector< std::vector<double> > &state, double total_time,
    int number_of_steps, double initial_time = 0) override;
  virtual void EvolveState(
    std::vector<double> &state, double total_time,
    int number_of_steps, double initial_time = 0) override;
  
};

#endif

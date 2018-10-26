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

  bool needs_initialization = true;

  void InitializeFirstState(double time_step, double initial_time = 0);

  std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >*
    StateToPositions(const std::vector< std::vector<double> >& state);
  void DeletePoints(
    const std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >& points);

protected:
  void StepState(double time_step, double time = 0) override;

  ODESolver& initial_solver;

public:
  VerletIntegrator(unsigned int dimension = 2);
  VerletIntegrator(SmoothCoordinateSpace* space);
  VerletIntegrator(ODEInterface *differential_equation, unsigned int dimension = 2);
  VerletIntegrator(ODEInterface *differential_equation, SmoothCoordinateSpace* space);
  VerletIntegrator(ODEInterface *differential_equation, SmoothCoordinateSpace* space,
    ODESolver& initial_solver);

  void setState(const std::vector< std::vector<double> > &state);
  void setState(const std::vector<double> &state);
};

#endif

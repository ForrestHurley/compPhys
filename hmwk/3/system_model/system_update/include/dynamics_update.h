#ifndef DYNAMICS_UPDATE_H
#define DYNAMICS_UPDATE_H

#include "basic_update.h"
#include "ode_solver.h"
#include "hamiltonian_particle_system.h"

class DynamicsUpdate : public BasicUpdate
{
private:
  class DynamicsODE : public ODEInterface
  {
    HamiltonianParticleSystem& system;
  public:
    bool preserve_state;

    DynamicsODE(HamiltonianParticleSystem& system, bool preserve_state = false);

    std::vector<double> CalculateHighestDerivative(
      const std::vector< std::vector<double> > &values, double time) override;
  };

  ODESolver& solver;
  DynamicsODE ode;

public:
  double step_time;
  double total_time;

  DynamicsUpdate(HamiltonianParticleSystem& system, ODESolver& solver, double step_time = 1., double initial_time = 0.);

  virtual void RunUpdate() override;

private:
  static std::vector<double> toVector(
    const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& state_variables);
  static void fromVector(
    const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& state_variables,
    const std::vector<double>& new_state);

};

#endif

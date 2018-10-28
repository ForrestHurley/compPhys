#ifndef METROPOLIS_DYNAMICS_UPDATE_H
#define METROPOLIS_DYNAMICS_UPDATE_H

#include "metropolis_update.h"
#include "dynamics_update.h"
#include <type_traits>

template <class MetropolisType>
class MetropolisDynamicsUpdate : public BasicUpdate
{
  static_assert(std::is_base_of<MetropolisUpdate, MetropolisType>::value,
    "MetropolisType must inherit from MetropolisUpdate");
public:
  MetropolisType metropolis;
  DynamicsUpdate dynamics;

public:
  MetropolisDynamicsUpdate(ClassicalParticleSystem& system, ODESolver& solver,
    double step_time = 1., double initial_time = 0., bool use_classical_ode = true);

  virtual void RunUpdate() override;
};

template <class MetropolisType>
MetropolisDynamicsUpdate<MetropolisType>::MetropolisDynamicsUpdate(ClassicalParticleSystem& system, ODESolver& solver,
  double step_time, double initial_time, bool use_classical_ode) :
  BasicUpdate(system),
  dynamics(system, solver, step_time, initial_time),
  metropolis(system) {}

template <class MetropolisType>
void MetropolisDynamicsUpdate<MetropolisType>::RunUpdate()
{
  dynamics.SetupUpdate();
  dynamics.RunUpdate();
  metropolis.SetupUpdate();
  metropolis.RunUpdate();
}

#endif

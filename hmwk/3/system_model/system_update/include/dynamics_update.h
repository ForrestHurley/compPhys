#ifndef DYNAMICS_UPDATE_H
#define DYNAMICS_UPDATE_H

#include "basic_update.h"
#include "ode_solver.h"

class DynamicsUpdate : public BasicUpdate
{
private:
  ODESolver& solver;
public:
  DynamicsUpdate(ParticleSystem& system, ODESolver& solver);

  virtual void RunUpdate() override;
};

#endif

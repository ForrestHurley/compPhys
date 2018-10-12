#include "dynamics_update.h"

DynamicsUpdate::DynamicsUpdate(ParticleSystem& system, ODESolver& solver) :
  BasicUpdate(system), solver(solver) {}

void DynamicsUpdate::RunUpdate() {}


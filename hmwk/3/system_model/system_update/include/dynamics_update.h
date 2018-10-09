#ifndef DYNAMICS_UPDATE_H
#define DYNAMICS_UPDATE_H

#include "basic_update.h"

class DynamicsUpdate : public BasicUpdate
{
public:
  DynamicsUpdate(ParticleSystem& system, ODESolver& solver);

  virtual void RunUpdate() override;
};

#endif

#ifndef METRIPOLIS_UPDATE_H
#define METROPOLIS_UPDATE_H

#include "basic_update.h"

class MetropolisUpdate : public BasicUpdate
{
public:
  MetropolisUpdate(ParticleSystem& system);

  virtual void RunUpdate() override;
};

#endif

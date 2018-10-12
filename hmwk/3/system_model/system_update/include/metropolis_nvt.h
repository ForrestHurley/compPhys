#ifndef METROPOLIS_NVT_H
#define METROPOLIS_NVT_H

#include "metropolis_update.h"

class MetropolisNVTUpdate : public MetropolisUpdate
{
public:
  const double T;

  MetropolisNVTUpdate(ParticleSystem& system, double T);

  virtual void RunUpdate() override;
};

#endif

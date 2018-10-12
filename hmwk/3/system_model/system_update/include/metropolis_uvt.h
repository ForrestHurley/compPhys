#ifndef METROPOLIS_UVT_H
#define METROPOLIS_UVT_H

#include "metropolis_update.h"

class MetropolisUVTUpdate : public MetropolisUpdate
{
public:
  const double T, U;

  MetropolisUVTUpdate(ParticleSystem& system, double T, double U);

  virtual void RunUpdate() override;
};

#endif

#ifndef METROPOLIS_UVT_H
#define METROPOLIS_UVT_H

#include "metropolis_update.h"

class MetropolisUVTUpdate : public MetropolisUpdate
{
public:
  const double T, U;

  MetropolisUVTUpdate(ClassicalParticleSystem& system, double T = 1., double U = 1.);

  virtual void RunUpdate() override;
};

#endif

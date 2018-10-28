#ifndef METROPOLIS_NPT_H
#define METROPOLIS_NPT_H

#include "metropolis_update.h"

class MetropolisNPTUpdate : public MetropolisUpdate
{
public:
  const double T, P;

  MetropolisNPTUpdate(ClassicalParticleSystem& system, double T = 1., double P = 1.);

  virtual void RunUpdate() override;
};

#endif

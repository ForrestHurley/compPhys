#ifndef METROPOLIS_NPT_H
#define METROPOLIS_NPT_H

#include "metropolis_update.h"

class MetropolisNPTUpdate : public MetropolisUpdate
{
public:
  const double T, P;

  MetropolisNPTUpdate(ParticleSystem& system, double T, double P);

  virtual void RunUpdate() override;
};

#endif

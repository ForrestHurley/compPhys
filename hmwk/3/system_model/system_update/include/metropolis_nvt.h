#ifndef METROPOLIS_NVT_H
#define METROPOLIS_NVT_H

#include "metropolis_update.h"

class MetropolisNVTUpdate : public MetropolisUpdate
{
private:
  double beta;
  double k_b;
  double T;

public:
  MetropolisNVTUpdate(ClassicalParticleSystem& system, double T = 1., double k_b = 1.);

  void setT(double new_t, double k_b = 1.);
  double getT() const;

  virtual void RunUpdate() override;
};

#endif

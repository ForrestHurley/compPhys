#ifndef METROPOLIS_DYNAMICS_UPDATE_H
#define METROPOLIS_DYNAMICS_UPDATE_H

#include "metropolist_update.h"
#include <type_traits>

template <class MetropolisType>
class MetropolisDynamicsUpdate : public BasicUpdate
{
  static_assert(std::is_base_of<MetropolisUpdate, MetropolisType>::value,
    "MetropolisType must inherit from MetropolisUpdate");
private:
  MetropolisType metropolis;
  DynamicsUpdate dynamics;
public:
  MetropolisDynamicsUpdate(ParticleSystem& system, ODESolver& solver);

  virtual RunUpdate() override;
};

#endif

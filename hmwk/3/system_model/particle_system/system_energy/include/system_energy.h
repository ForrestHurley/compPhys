#ifndef SYSTEM_ENERGY_H
#define SYSTEM_ENERGY_H

#include "particle_state.h"

class SystemEnergy
{
protected:
  const ParticleState& state;

public:
  SystemEnergy(const ParticleState& state);

  virtual double Energy() const = 0;
};

#endif

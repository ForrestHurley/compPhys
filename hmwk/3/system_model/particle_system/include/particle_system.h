#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "system_energy.h"
#include "particle_state.h"

class ParticleSystem
{
protected:
  const SystemEnergy& system_energy;
  ParticleState& state;
public:
  ParticleSystem(const SystemEnergy& system_energy, ParticleState& initial_state);

  virtual ParticleState& getState();
  virtual const ParticleState& getCurrentState() const;
  virtual double getCurrentEnergy() const;
};

#endif

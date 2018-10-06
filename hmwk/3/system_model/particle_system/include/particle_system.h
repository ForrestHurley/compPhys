#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

class ParticleSystem
{
protected:
  const SystemEnergy& system_energy;
  const ParticleState& state;
public:
  ParticleSystem(const SystemEnergy& system_energy, const ParticleState& initial_state);

  virtual const ParticleState& getCurrentState();
  virtual double getCurrentEnergy();
};

#endif

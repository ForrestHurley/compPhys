#ifndef HAMILTONIAN_PARTICLE_SYSTEM_H
#define HAMILTONIAN_PARTICLE_SYSTEM_H

#include "hamiltonian_particle_state.h"
#include "particle_system.h"
#include "hamiltonian_energy.h"
#include "hamiltonian_particle_state.h"

class HamiltonianParticleSystem : public ParticleSystem
{
private:
  const HamiltonianParticleState& hamiltonian_state;

public:
  HamiltonianParticleSystem(const HamiltonianEnergy& system_energy, const HamiltonianParticleState& initial_state);

  const HamiltonianParticleState& getCurrentState() override;
  virtual double getPositionPartial() const;
  virtual double getMomentumPartial() const;
};

#endif

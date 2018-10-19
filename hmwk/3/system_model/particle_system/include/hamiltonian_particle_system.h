#ifndef HAMILTONIAN_PARTICLE_SYSTEM_H
#define HAMILTONIAN_PARTICLE_SYSTEM_H

#include "hamiltonian_particle_state.h"
#include "particle_system.h"
#include "hamiltonian_energy.h"
#include "hamiltonian_particle_state.h"

class HamiltonianParticleSystem : public ParticleSystem
{
protected:
  const HamiltonianEnergy& getHamiltonianEnergy() const;

public:
  HamiltonianParticleSystem(const HamiltonianEnergy& system_energy, const HamiltonianParticleState& initial_state);

  const HamiltonianParticleState& getCurrentState() const override;
  virtual std::vector<Coordinate> getPositionPartial() const;
  virtual std::vector<Coordinate> getMomentumPartial() const;
};

#endif

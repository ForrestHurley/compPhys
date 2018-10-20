#ifndef CLASSICAL_PARTICLE_SYSTEM_H
#define CLASSICAL_PARTILCE_SYSTEM_H

#include "hamiltonian_particle_system.h"
#include "potential_energy.h"
#include "classical_hamiltonian_energy.h"

class ClassicalParticleSystem : public HamiltonianParticleSystem
{
protected:
  ClassicalHamiltonian hamiltonian;

public:
  ClassicalParticleSystem(
    const PotentialEnergy& potential_energy,
    HamiltonianParticleState& initial_state);
  
  virtual double getKineticEnergy() const;
  virtual double getPotentialEnergy() const;
};

#endif

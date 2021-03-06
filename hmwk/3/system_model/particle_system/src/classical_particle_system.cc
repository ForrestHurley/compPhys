#include "classical_particle_system.h"

ClassicalParticleSystem::ClassicalParticleSystem(
  const PotentialEnergy& potential_energy,
  HamiltonianParticleState& initial_state) :
  hamiltonian(initial_state, potential_energy), HamiltonianParticleSystem(hamiltonian, initial_state) {};

double ClassicalParticleSystem::getKineticEnergy() const
{
  return hamiltonian.MomentumEnergy();
}

double ClassicalParticleSystem::getPotentialEnergy() const
{
  return hamiltonian.PositionEnergy();
}

#include "hamiltonian_particle_system.h"

HamiltonianParticleSystem::HamiltonianParticleSystem(const HamiltonianEnergy& system_energy,
  const HamiltonianParticleState& initial_state) :
  ParticleSystem(system_energy, initial_state), hamiltonian_state(initial_state) {}

const HamiltonianParticleState& HamiltonianParticleSystem::getCurrentState()
{
  return hamiltonian_state;
}

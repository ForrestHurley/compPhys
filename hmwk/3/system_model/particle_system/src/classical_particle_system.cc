#include "classical_particle_system.h"

ClassicalParticleSystem::ClassicalParticleSystem(const PotentialEnergy& potential_energy,
  const HamiltonianParticleState& initial_state) :
  hamiltonian(initial_state, potential_energy), HamiltonianParticleSystem(hamiltonian, initial_state) {};

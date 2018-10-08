#include "classical_pairwise_particle_system.h"

ClassicalPairwiseParticleSystem::ClassicalPairwiseParticleSystem(
  const PairwisePotentialFunction& pairwise_potential,
  const HamiltonianParticleState& initial_state) :
  pairwise_potential_energy(initial_state.getPositionReference(), pairwise_potential), 
  ClassicalParticleSystem(pairwise_potential_energy, initial_state) {}

#include "classical_pairwise_particle_system.h"

ClassicalPairwiseParticleSystem::ClassicalPairwiseParticleSystem(
  const PairwisePotentialFunction& pairwise_potential,
  HamiltonianParticleState& initial_state) :
    pairwise_potential_energy(initial_state.getPositions(), pairwise_potential), 
    ClassicalParticleSystem(pairwise_potential_energy, initial_state) {}

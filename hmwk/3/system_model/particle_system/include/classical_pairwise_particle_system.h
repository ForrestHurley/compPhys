#ifndef CLASSICAL_PAIRWISE_PARTICLE_SYSTEM_H
#define CLASSICAL_PAIRWISE_PARTICLE_SYSTEM_H

#include "classical_particle_system.h"
#include "pairwise_potential_function.h"

class ClassicalPairwiseParticleSystem : public ClassicalParticleSystem
{
public:
  ClassicalPairwiseParticleSystem(const PairwisePotentialFunction& pairwise_potential, const HamiltonianParticleState& initial_state);
};

#endif

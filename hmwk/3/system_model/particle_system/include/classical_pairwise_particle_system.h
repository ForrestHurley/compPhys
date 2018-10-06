#ifndef CLASSICAL_PAIRWISE_PARTICLE_SYSTEM_H
#define CLASSICAL_PAIRWISE_PARTICLE_SYSTEM_H

class ClassicalPairwiseParticleSystem : public ClassicalParticleSystem
{
public:
  ClassicalPairwiseParticleSystem(const PairwisePotentialFunction& pairwise_potential, const HamiltonianState& initial_state);
};

#endif

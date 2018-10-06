#ifndef CLASSICAL_PARTICLE_SYSTEM_H
#define CLASSICAL_PARTILCE_SYSTEM_H

class ClassicalParticleSystem : public HamiltonianParticleSystem
{
public:
  ClassicalParticleSystem(const PotentialEnergy& potential_energy, const HamiltonianState& initial_state);
};

#endif

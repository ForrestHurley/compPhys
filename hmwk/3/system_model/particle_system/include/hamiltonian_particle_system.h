#ifndef HAMILTONIAN_PARTICLE_SYSTEM_H
#define HAMILTONIAN_PARTICLE_SYSTEM_H

class HamiltonianParticleSystem : public ParticleSystem
{
public:
  HamiltonianParticleSystem(const HamiltonianEnergy& system_energy, const HamiltonianState& initial_state);

  const HamiltonianState& getCurrentState() override;
};

#endif

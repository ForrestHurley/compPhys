#include "particle_system.h"

ParticleSystem::ParticleSystem(const SystemEnergy& system_energy, const ParticleState& initial_state) : 
  system_energy(system_energy), state(initial_state) {}

const ParticleState& ParticleSystem::getCurrentState() const
{
  return state;
}

double ParticleSystem::getCurrentEnergy() const
{
  return system_energy.Energy();
}

#include "particle_system.h"

ParticleSystem::ParticleSystem(const SystemEnergy& system_energy, ParticleState& initial_state) : 
  system_energy(system_energy), state(initial_state) {}

ParticleState& ParticleSystem::getState()
{
  return state;
}

const ParticleState& ParticleSystem::getCurrentState() const
{
  return state;
}

double ParticleSystem::getCurrentEnergy() const
{
  return system_energy.Energy();
}

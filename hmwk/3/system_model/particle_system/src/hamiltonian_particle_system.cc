#include "hamiltonian_particle_system.h"

HamiltonianParticleSystem::HamiltonianParticleSystem(
  const HamiltonianEnergy& system_energy,
  HamiltonianParticleState& initial_state) :
  ParticleSystem(system_energy, initial_state) {}

HamiltonianParticleState& HamiltonianParticleSystem::getState()
{
  return static_cast<HamiltonianParticleState&>(state);
}

const HamiltonianParticleState& HamiltonianParticleSystem::getCurrentState() const
{
  return static_cast<HamiltonianParticleState&>(state);
}

std::vector<Coordinate> HamiltonianParticleSystem::getPositionPartial() const
{
  return getHamiltonianEnergy().PositionPartial();
}

std::vector<Coordinate> HamiltonianParticleSystem::getMomentumPartial() const
{
  return getHamiltonianEnergy().MomentumPartial();
}

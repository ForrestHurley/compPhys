#include "hamiltonian_particle_system.h"

HamiltonianParticleSystem::HamiltonianParticleSystem(
  const HamiltonianEnergy& system_energy,
  const HamiltonianParticleState& initial_state) :
  ParticleSystem(system_energy, initial_state) {}

const HamiltonianParticleState& HamiltonianParticleSystem::getCurrentState() const
{
  return static_cast<const HamiltonianParticleState&>(state);
}

std::vector<Coordinate> HamiltonianParticleSystem::getPositionPartial() const
{
  return getHamiltonianEnergy().PositionPartial();
}

std::vector<Coordinate> HamiltonianParticleSystem::getMomentumPartial() const
{
  return getHamiltonianEnergy().MomentumPartial();
}

#include "hamiltonian_particle_state.h"

HamiltonianParticleState::HamiltonianParticleState() {}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>&
  HamiltonianParticleState::getPositions() const
{
  return getStateComponent(0); //0 is the positions
}

void HamiltonianParticleState::setPositions(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& new_positions)
{
  setStateComponent(new_positions, 0);
}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>&
  HamiltonianParticleState::getMomenta() const
{
  return getStateComponent(1); //1 is the momenta
}

void HamiltonianParticleState::setMomenta(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& new_momenta)
{
  setStateComponent(new_momenta, 1);
} 

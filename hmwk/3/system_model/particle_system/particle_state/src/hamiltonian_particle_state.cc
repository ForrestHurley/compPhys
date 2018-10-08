#include "hamiltonian_particle_state.h"

HamiltonianParticleState::HamiltonianParticleState() {}

std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> HamiltonianParticleState::getPositions() const
{
  return getStateComponent(0);
}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>&
  HamiltonianParticleState::getPositionReference() const
{
  return state.at(0);
}

void HamiltonianParticleState::setPositions(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>
  new_positions) {}

std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> HamiltonianParticleState::getMomenta() const
{
  return getStateComponent(1);
}

void HamiltonianParticleState::setMomenta(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> new_momenta) {} 

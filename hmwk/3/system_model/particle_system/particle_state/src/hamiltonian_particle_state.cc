#include "hamiltonian_particle_state.h"

HamiltonianParticleState::HamiltonianParticleState(
  SmoothCoordinateSpace* position_space,
  SmoothCoordinateSpace* momentum_space) :
  ParticleState(std::vector<SmoothCoordinateSpace*>{position_space, momentum_space}) {}

void HamiltonianParticleState::AddParticle(
  const Coordinate& position,
  const Coordinate& momentum)
{
  ParticleState::AddParticle(std::vector<Coordinate>{position, momentum});
}

void HamiltonianParticleState::AddStationaryParticle(
  const Coordinate& position)
{
  AddParticle(
    position,
    coordinate_spaces.at(1)->getOrigin().getCoordinate());
}

SmoothCoordinateSpace* HamiltonianParticleState::getPositionSpace() const
{
  return getComponentSpace(0);
}

SmoothCoordinateSpace* HamiltonianParticleState::getMomentumSpace() const
{
  return getComponentSpace(1);
}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>&
  HamiltonianParticleState::getPositions() const
{
  return getStateComponent(0); //0 is the positions
}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>&
  HamiltonianParticleState::getMomenta() const
{
  return getStateComponent(1); //1 is the momenta
}

#include "particle_state.h"


ParticleState::ParticleState(const std::vector<SmoothCoordinateSpace* >& coordinate_spaces) : 
  coordinate_spaces(coordinate_spaces) {}

ParticleState::~ParticleState()
{
  for (int i = 0; i < state.size(); i++)
  {
    for (SmoothCoordinateSpace::SmoothCoordinatePoint* coordinate: state.at(i))
      delete coordinate;
  }
}

void ParticleState::AddOriginParticle()
{
  std::vector<Coordinate> origins;
  for (SmoothCoordinateSpace* space : coordinate_spaces)
    origins.push_back(space->getOrigin().getCoordinate());
}

void ParticleState::AddParticle(const std::vector<Coordinate>& particle_state)
{
  assert(particle_state.size() == state.size());
  for (int i = 0; i < particle_state.size(); i++)
    state.at(i).push_back(
      &coordinate_spaces.at(i)->CreatePoint(particle_state.at(i)));
}

const std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> >& ParticleState::getState() const
{
  return state;
}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& ParticleState::getStateComponent(
  int component_number) const
{
  return state.at(component_number);
}


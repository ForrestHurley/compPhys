#include "particle_state.h"

const std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> >& ParticleState::getState() const
{
  return state;
}

void ParticleState::setState(
  const std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> >& new_state) 
{
  state = new_state;
}

const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& ParticleState::getStateComponent(
  int component_number) const
{
  return state.at(component_number);
}

void ParticleState::setStateComponent(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& new_component,
  int component_number)
{
  state.at(component_number) = new_component;
}

#include "particle_state.h"

std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> > ParticleState::getState() const
{
  return state;
}

void ParticleState::setState(std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> > new_state) {}

std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> ParticleState::getStateComponent(int component_number) const
{
  return state.at(0);
}

void ParticleState::setStateComponent(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> new_component, int component_number) {}

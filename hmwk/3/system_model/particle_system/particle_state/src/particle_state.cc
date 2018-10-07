#include "particle_state.h"

std::vector< std::vector<Coordinate> > ParticleState::getState()
{
  return state;
}

void ParticleState::setState(std::vector< std::vector<Coordinate> > new_state) {}

std::vector<Coordinate> ParticleState::getStateComponent(int component_number)
{
  return state.at(0);
}

void ParticleState::setStateComponent(std::vector<Coordinate> new_component, int component_number) {}

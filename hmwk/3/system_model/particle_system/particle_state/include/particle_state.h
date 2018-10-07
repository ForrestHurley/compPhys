#ifndef PARTICLE_STATE_H
#define PARTICLE_STATE_H

#include <vector>
#include "coordinate.h"

class ParticleState
{
private:
  std::vector< std::vector<Coordinate> > state;
public:
  std::vector< std::vector<Coordinate> > getState();
  void setState(std::vector< std::vector<Coordinate> > new_state);

  std::vector<Coordinate> getStateComponent(int component_number);
  void setStateComponent(std::vector<Coordinate> new_component, int component_number);
};

#endif

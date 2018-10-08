#ifndef PARTICLE_STATE_H
#define PARTICLE_STATE_H

#include <vector>
#include "coordinate.h"
#include "smooth_coordinate_space.h"

class ParticleState
{
protected:
  std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> > state;
public:
  std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> > getState() const;
  void setState(std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> > new_state);

  std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> getStateComponent(int component_number) const;
  void setStateComponent(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> new_component, int component_number);
};

#endif

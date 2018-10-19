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
  const std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> >& getState() const;
  void setState(const std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> >& new_state);

  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getStateComponent(int component_number) const;
  void setStateComponent(
    const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& new_component,
    int component_number);
};

#endif

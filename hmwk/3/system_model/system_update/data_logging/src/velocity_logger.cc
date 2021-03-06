#include "velocity_logger.h"
#include <iostream>

VelocityLogger::VelocityLogger(const HamiltonianParticleSystem& system)
  : DataLogger(system) {}

void VelocityLogger::Log(double current_time)
{
  times.push_back(current_time);

  const HamiltonianParticleState& state =
    static_cast<const HamiltonianParticleSystem&>(system)
    .getCurrentState();

  std::vector<Coordinate> step;

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* particle : 
    state.getMomenta())
    step.push_back(particle->getCoordinate());

  velocities.push_back(step);
}

int VelocityLogger::getLogCount() const
{
  return times.size();
}

std::ostream& operator<<(
  std::ostream &os, const VelocityLogger &logger)
{
  for (int i = 0; i < logger.getLogCount(); i++)
  {
    os << logger.times.at(i);
    for (int j = 0; j < logger.velocities.at(i).size(); j++)
      os << "," << logger.velocities.at(i).at(j);
    os << std::endl;
  }
  return os;
}

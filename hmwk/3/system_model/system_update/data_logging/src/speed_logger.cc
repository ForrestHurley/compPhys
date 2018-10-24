#include "speed_logger.h"
#include <iostream>

SpeedLogger::SpeedLogger(const HamiltonianParticleSystem& system)
  : DataLogger(system) {}

void SpeedLogger::Log(double current_time)
{
  times.push_back(current_time);

  const HamiltonianParticleState& state =
    static_cast<const HamiltonianParticleSystem&>(system)
    .getCurrentState();

  std::vector<double> step;

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* particle : 
    state.getMomenta())
    step.push_back(particle->getCoordinate().getMagnitude());

  speeds.push_back(step);
}

int SpeedLogger::getLogCount() const
{
  return times.size();
}

std::ostream& operator<<(
  std::ostream &os, const SpeedLogger &logger)
{
  for (int i = 0; i < logger.getLogCount(); i++)
    os << logger.times.at(i) << ":";
    for (int j = 0; j < logger.speeds.at(i).size(); j++)
      os << logger.speeds.at(i).at(j) << ",";
  return os;
}

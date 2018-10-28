#include "position_logger.h"
#include <iostream>

PositionLogger::PositionLogger(const HamiltonianParticleSystem& system)
  : DataLogger(system) {}

void PositionLogger::Log(double current_time)
{
  times.push_back(current_time);

  const HamiltonianParticleState& state =
    static_cast<const HamiltonianParticleSystem&>(system)
    .getCurrentState();

  std::vector<Coordinate> step;

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* particle :
    state.getPositions())
    step.push_back(particle->getCoordinate());

  positions.push_back(step);
}

int PositionLogger::getLogCount() const
{
  return times.size();
}

std::ostream& operator<<(
  std::ostream &os, const PositionLogger &logger)
{
  for (int i = 0; i < logger.getLogCount(); i++)
  {
    os << logger.times.at(i);
    for (int j = 0; j < logger.positions.at(i).size(); j++)
      os << "," << logger.positions.at(i).at(j);
    os << std::endl;
  }
  return os;
}

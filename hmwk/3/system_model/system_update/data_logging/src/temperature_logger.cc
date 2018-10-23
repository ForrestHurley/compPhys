#include "temperature_logger.h"
#include <iostream>

TemperatureLogger::TemperatureLogger(
  const ClassicalParticleSystem& system) :
  DataLogger(system) {}

void TemperatureLogger::Log(double current_time)
{
  times.push_back(current_time);

  const ClassicalParticleSystem& classical_system =
    static_cast<const ClassicalParticleSystem&>(system);

  const double temperature =
    2 * classical_system.getKineticEnergy() /
    (3 * classical_system.getCurrentState().getParticleCount() - 3);

  temperatures.push_back(temperature);
}

int TemperatureLogger::getLogCount() const
{
  return times.size();
}

std::ostream& operator<<(
  std::ostream &os, const TemperatureLogger &logger)
{
  for (int i = 0; i < logger.getLogCount(); i++)
    os << logger.times.at(i) << "," << logger.temperatures.at(i) << std::endl;
  return os;
}

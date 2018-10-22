
#include "energy_logger.h"

EnergyLogger::EnergyLogger(const ParticleSystem& system)
  : DataLogger(system) {}

void EnergyLogger::Log(double current_time)
{
  energies.push_back(
    system.getCurrentEnergy());
  times.push_back(current_time);
}

int EnergyLogger::getLogCount() const
{
  return energies.size();
}

std::ostream& operator<<(
  std::ostream &os, const EnergyLogger &logger)
{
  for (int i = 0; i < logger.getLogCount(); i++)
    os << logger.times.at(i) << ":" << logger.energies.at(i) << std::endl;
}

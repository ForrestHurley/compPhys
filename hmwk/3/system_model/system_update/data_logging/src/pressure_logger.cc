
#include "pressure_logger.h"

PressureLogger::PressureLogger(const ClassicalParticleSystem& system)
  : DataLogger(system) {}

void PressureLogger::Log(double current_time)
{

}

int PressureLogger::getLogCount() const
{

}

std::ostream& operator<<(
  std::ostream &os, const PressureLogger &logger);

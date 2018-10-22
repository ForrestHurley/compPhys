
#include "displacement_logger.h"

DisplacementLogger::DisplacementLogger(
  const HamiltonianParticleSystem& system) :
  DataLogger(system) {}

void DisplacementLogger::Log(double current_time)
{

}

int DisplacementLogger::getLogCount() const
{

}

std::ostream& operator<<(
  std::ostream &os, const DisplacementLogger &logger)
{

}

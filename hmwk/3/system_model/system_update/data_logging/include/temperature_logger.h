#ifndef TEMPERATURE_LOGGER_H
#define TEMPERATURE_LOGGER_H

#include "data_logger.h"
#include "classical_particle_system.h"
#include <vector>

class TemperatureLogger final : public DataLogger
{
private:
  std::vector<double> temperature;
  std::vector<double> time;
public:
  TemperatureLogger(const ClassicalParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const TemperatureLogger &logger);
}

#endif

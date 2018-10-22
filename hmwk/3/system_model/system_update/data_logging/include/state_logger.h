#ifndef STATE_LOGGER_H
#define STATE_LOGGER_H

#include "data_logger.h"

//TODO: probably needs a better copy constructor for particle state
class StateLogger final : public DataLogger
{
public:
  StateLogger(const ParticleSystem& system);

  void Log(double current_time) override;
  void getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const StateLogger &logger);
};

#endif

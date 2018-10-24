#ifndef SPEED_LOGGER_H
#define SPEED_LOGGER_H

class SpeedLogger : public DataLogger
{
private:
  std::vector<std::vector<double> > speeds;
  std::vector<double> times;

public:
  SpeedLogger(const HamiltonianParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const SpeedLogger &logger);

};

#endif

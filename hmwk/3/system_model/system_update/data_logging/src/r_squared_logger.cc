#include "r_squared_logger.h"

RSquaredLogger::RSquaredLogger(const HamiltonianParticleSystem& system) :
  DataLogger(system), 
  displacement_logger(*new DisplacementLogger(system)), 
  owns_displacement_logger(true) {}

RSquaredLogger::RSquaredLogger(DisplacementLogger& displacement_logger) :
  DataLogger(displacement_logger.getSystem()),
  displacement_logger(displacement_logger),
  owns_displacement_logger(false) {}

RSquaredLogger::~RSquaredLogger()
{
  if (owns_displacement_logger)
    delete &displacement_logger;
}
  
void RSquaredLogger::Log(double current_time)
{
  if (owns_displacement_logger)
    displacement_logger.Log(current_time);

  times.push_back(current_time);

  double mean = 0.;
  std::vector<double> tmp_r_squared;
  for (const Coordinate& point : 
    displacement_logger.total_displacements.at(
      displacement_logger.getLogCount() - 1))
  {
    const double magn = point.getMagnitudeSquared();
    tmp_r_squared.push_back(magn);
    mean += magn;
  }

  mean /= tmp_r_squared.size();

  displacement_magnitude_squared.push_back(
    tmp_r_squared);
  mean_r_squared.push_back(mean);
}

int RSquaredLogger::getLogCount() const
{
  return times.size();
}

std::ostream& operator<<(
  std::ostream &os, const RSquaredLogger &logger)
{
  for (int i = 0; i < logger.getLogCount(); i++)
    os << logger.times.at(i) << "," << 
      logger.mean_r_squared.at(i) << std::endl;
  return os;
}
  

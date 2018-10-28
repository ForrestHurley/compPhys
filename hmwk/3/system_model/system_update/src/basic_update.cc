#include "basic_update.h"
#include <chrono>

BasicUpdate::BasicUpdate(ParticleSystem& system) : system(system) {};

void BasicUpdate::RunUpdateN(int total_steps, bool verbose)
{
  for (DataLogger* logger : logger_list)
    logger->Log(0.);

  SetupUpdate();
  for (int i = 0; i < total_steps; i++)
  {
    if (verbose)
      if (i % 100 == 0)
        std::cout << "\r" <<
        "Currently on calculation " << i << 
        " out of " << total_steps;

    RunUpdate();
    for (DataLogger* logger : logger_list)
      logger->Log(i + 1.);
  }
  if (verbose)
    std::cout << std::endl;
}

void BasicUpdate::RunUpdateForDuration(double total_time)
{
  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds;

  for (DataLogger* logger : logger_list)
    logger->Log(0.);

  SetupUpdate();
  while (true)
  {
    RunUpdate();

    elapsed_seconds = std::chrono::system_clock::now() - start;
    for (DataLogger* logger : logger_list)
      logger->Log(elapsed_seconds.count());

    if (elapsed_seconds.count() > total_time)
      break;
  }
}

void BasicUpdate::addLogger(DataLogger* logger)
{
  logger_list.push_back(logger);
}

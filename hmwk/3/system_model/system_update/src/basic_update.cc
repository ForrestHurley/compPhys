#include "basic_update.h"
#include <chrono>

BasicUpdate::BasicUpdate(ParticleSystem& system) : system(system) {};

void BasicUpdate::RunUpdateN(int total_steps)
{
  for (int i = 0; i < total_steps; i++)
    RunUpdate();
}

void BasicUpdate::RunUpdateForDuration(double total_time)
{
  std::chrono::time_point<std::chrono::system_clock> start;
  start = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds;

  while (true)
  {
    RunUpdate();

    elapsed_seconds = std::chrono::system_clock::now() - start;
    if (elapsed_seconds.count() > total_time)
      break;
  }
}

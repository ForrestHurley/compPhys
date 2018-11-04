#include "state.h"
#include "diffusion.h"
#include "diffusion_monte_carlo.h"
#include <iostream>

int main()
{
  std::cout << "Starting things!" << std::endl;

  //Nucleus count, electron count, guess, dimension, walker count
  DiffusionMonteCarlo simulator
    = DiffusionMonteCarlo(2, 2, -2.9, 3, 1000);
    
  int initial_iterations = 0;
  int iterations_per_print = 100;
  double iteration_time_step = 0.00001;

  //Iterations, time step
  simulator.RunIterations(initial_iterations, iteration_time_step);

  for (int i = 0; i < 2000; i++)
  {
    double total_energy = 0.;
    for (double energy : simulator.getPastCalculatedEnergies())
      total_energy += energy;
    total_energy /= simulator.getPastCalculatedEnergies().size();

    std::cout << "Calculated energy is " << 
      total_energy << " after " <<
      i * iterations_per_print + initial_iterations << " iterations" << std::endl;

    simulator.ClearCalculatedEnergies();

    simulator.RunIterations(iterations_per_print, iteration_time_step);
  }
}

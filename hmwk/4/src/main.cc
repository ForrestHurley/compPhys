
#include "state.h"
#include "diffusion.h"
#include "diffusion_monte_carlo.h"
#include <iostream>

int main()
{
  std::cout << "Starting things!" << std::endl;

  //Nucleus count, electron count, guess, dimension, walker count
  DiffusionMonteCarlo simulator
    = DiffusionMonteCarlo(2, 2, -2.9, 3, 100000);
    
  //Iterations, time step
  simulator.RunIterations(1000, 0.001);

  for (int i = 0; i < 20; i++)
  {
    std::cout << "Calculated energy is " << 
      simulator.getCalculatedEnergy() << " after " <<
      i * 0.1 + 1 << " seconds" << std::endl;

    /*std::list<State>::const_iterator it;
    for (it = simulator.getWalkers().begin(); it != simulator.getWalkers().end(); it++)
    {
      for (int k = 0; k < it->dimension; k++)
      {
        std::cout << it->at(k) << ",";
      }
      std::cout << std::endl;
    }*/

    simulator.RunIterations(1000, 0.0001);
  }
}

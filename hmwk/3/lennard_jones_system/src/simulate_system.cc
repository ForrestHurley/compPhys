
#include "hamiltonian_particle_state.h"
#include "dynamics_update.h"
#include "classical_pairwise_particle_system.h" 
#include "lennard_jones_potential.h"
#include "integ_runge_kutta.h"
#include "flat_torus_space.h"
#include "euclidean_space.h"
#include "energy_logger.h"
#include <iostream>

//TODO:   Create better bounds (and support non-zero minimums on everything)
//        Allow proper verlet with bounds
//        Data collection class!
//        Test and write tests

int main()
{
  std::cout << "Declaring potential" << std::endl;
  LennardJonesPotential pairwise_potential = LennardJonesPotential();
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(false);

  std::cout << "Declaring coordinate systems" << std::endl;
  //Initialize coordinate systems
  std::vector<double> bounds{ 10., 10. };
  std::cout << "Euclidean coordinate system" << std::endl;
  EuclideanSpace momentum_coordinate_system = EuclideanSpace(bounds.size());
  std::cout << "Torus coordinate system" << std::endl;
  FlatTorusSpace position_coordinate_system = FlatTorusSpace(bounds);

  std::cout << "Creating particle state" << std::endl;
  //Create particle state
  
  HamiltonianParticleState state = HamiltonianParticleState(
    &position_coordinate_system,
    &momentum_coordinate_system);

  std::cout << "Adding particles" << std::endl;
  //Add particles to state
  /*for (int i = 0; i < 16; i++)
    state.AddStationaryParticle(
      Coordinate(std::vector<double>{1. + i % 4, 1. + i / 4}));*/
  state.AddStationaryParticle(
    Coordinate(std::vector<double>{2, 2}));
  state.AddStationaryParticle(
    Coordinate(std::vector<double>{2, 3}));

  std::cout << "Declaring system" << std::endl;
  //Initialize the state-energy pair (system)
  ClassicalPairwiseParticleSystem system =
    ClassicalPairwiseParticleSystem(pairwise_potential, state);

  std::cout << "Creating energy logger" << std::endl;
  //Initialize data collection object
  EnergyLogger energy_logger = EnergyLogger(system);

  std::cout << "Building dynamics updater" << std::endl;
  //System, solver, step_time, initial_time, use_classical_ode
  DynamicsUpdate updater = DynamicsUpdate(system, integrator, 0.01, 0., false);

  updater.addLogger(&energy_logger);

  std::cout << "Simulating system" << std::endl;
  //Run dynamics simulation
  updater.RunUpdateN(50);

  std::cout << "Finished simulating" << std::endl;
  std::cout << "Outputting results" << std::endl;
  //Print results from data collection
  std::cout << energy_logger << std::endl;

  return 0;
}

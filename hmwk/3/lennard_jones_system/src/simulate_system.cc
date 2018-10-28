
#include "hamiltonian_particle_state.h"
#include "dynamics_update.h"
#include "classical_pairwise_particle_system.h" 
#include "lennard_jones_potential.h"
#include "integ_runge_kutta.h"
#include "integ_verlet.h"
#include "flat_torus_space.h"
#include "bounded_euclidean_space.h"
#include "euclidean_space.h"
#include "energy_logger.h"
#include "velocity_logger.h"
#include "temperature_logger.h"
#include "position_logger.h"
#include "coordinate_bounds.h"
#include "r_squared_logger.h"
#include <iostream>
#include <random>

//TODO:   Create better bounds (and support non-zero minimums on everything)
//        Allow proper verlet with bounds
//        Data collection class!
//        Test and write tests

int main()
{
  std::cout << "Declaring potential" << std::endl;
  LennardJonesPotential pairwise_potential = LennardJonesPotential();

  std::cout << "Declaring coordinate systems" << std::endl;
  //Initialize coordinate systems
  CoordinateBounds bounds = CoordinateBounds(
    std::vector<double>{ -0., -0. },
    std::vector<double>{ 10., 10.});

  CoordinateBounds velocity_bounds = CoordinateBounds(
    std::vector<double>{-1e4, -1e4},
    std::vector<double>{1e4, 1e4});

  std::cout << "Euclidean coordinate system" << std::endl;
  BoundedEuclideanSpace momentum_coordinate_system = 
    BoundedEuclideanSpace(velocity_bounds);
  std::cout << "Torus coordinate system" << std::endl;
  FlatTorusSpace position_coordinate_system = FlatTorusSpace(bounds);

  std::cout << "Creating particle state" << std::endl;
  //Create particle state
  
  HamiltonianParticleState state = HamiltonianParticleState(
    &position_coordinate_system,
    &momentum_coordinate_system);

  std::cout << "Adding particles" << std::endl;

  Coordinate scale =
    Coordinate(std::vector<double>{0.001,0.001});

  std::random_device device;
  std::mt19937_64 generator(device());

  //Add particles to state
  for (int i = 0; i < 16; i++)
    state.AddParticle(
      Coordinate(std::vector<double>{(double)(i % 4), 1. + i / 4}),
      Coordinate::RandomUnit(2, generator) * scale);
  /*state.AddStationaryParticle(
    Coordinate(std::vector<double>{6, 2}));
  state.AddStationaryParticle(
    Coordinate(std::vector<double>{6, 3.}));*/

  std::cout << "Declaring system" << std::endl;
  //Initialize the state-energy pair (system)
  ClassicalPairwiseParticleSystem system =
    ClassicalPairwiseParticleSystem(pairwise_potential, state);

  std::cout << "Creating loggers" << std::endl;
  //Initialize data collection object
  EnergyLogger energy_logger = EnergyLogger(system);
  VelocityLogger velocity_logger = VelocityLogger(system);
  TemperatureLogger temperature_logger = TemperatureLogger(system);
  RSquaredLogger r_squared_logger = RSquaredLogger(system);
  PositionLogger position_logger = PositionLogger(system);

  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(false);
  VerletIntegrator verlet_integrator = VerletIntegrator(&position_coordinate_system);

  std::cout << "Building dynamics updater" << std::endl;
  //System, solver, step_time, initial_time, use_classical_ode
  DynamicsUpdate updater = DynamicsUpdate(system, verlet_integrator, 0.005, 0., true);
  //DynamicsUpdate updater = DynamicsUpdate(system, integrator, 0.005, 0., true);

  updater.addLogger(&energy_logger);
  updater.addLogger(&velocity_logger);
  updater.addLogger(&temperature_logger);
  updater.addLogger(&r_squared_logger);
  updater.addLogger(&position_logger);

  std::cout << "Simulating system" << std::endl;
  //Run dynamics simulation
  updater.RunUpdateN(25);

  std::cout << "Finished simulating" << std::endl;
  std::cout << "Outputting results" << std::endl;
  //Print results from data collection
  std::cout << r_squared_logger << std::endl;
  
  return 0;
}

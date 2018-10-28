
#include "hamiltonian_particle_state.h"
#include "dynamics_update.h"
#include "metropolis_dynamics_update.h"
#include "metropolis_nvt.h"
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
#include <string>
#include <fstream>

void SaveVelocityDistribution(std::string file_name, const VelocityLogger& logger)
{
  std::vector<double> out_values;
  out_values.reserve(
    logger.getLogCount() * logger.getSystem().getCurrentState().getParticleCount());

  for (const std::vector<Coordinate>& velocities : logger.getVelocities())
    for (const Coordinate& coordinate : velocities)
      out_values.push_back(coordinate.getMagnitude());

  std::ofstream out_file(file_name);
  for (int i = 0; i < out_values.size(); i++)
    out_file << out_values.at(i) << std::endl;
  out_file.close();
}

void Problem1()
{
  std::cout << "Starting problem 1" << std::endl;
  std::cout << "Declaring potential" << std::endl;
  LennardJonesPotential pairwise_potential = LennardJonesPotential();

  std::cout << "Declaring coordinate systems" << std::endl;
  //Initialize coordinate systems
  CoordinateBounds bounds = CoordinateBounds(
    std::vector<double>{ -0., -0. },
    std::vector<double>{ 10., 10.});

  //Limits the maximum and minimum velocities
  CoordinateBounds velocity_bounds = CoordinateBounds(
    std::vector<double>{-1e6, -1e6},
    std::vector<double>{1e6, 1e6});

  BoundedEuclideanSpace momentum_coordinate_system =
    BoundedEuclideanSpace(velocity_bounds);
  FlatTorusSpace position_coordinate_system = FlatTorusSpace(bounds);

  std::cout << "Creating particle state" << std::endl;

  HamiltonianParticleState state = HamiltonianParticleState(
    &position_coordinate_system,
    &momentum_coordinate_system);

  std::cout << "Adding particles" << std::endl;

  Coordinate scale =
    Coordinate(std::vector<double>{1.5, 1.5});

  std::random_device device;
  std::mt19937_64 generator(device());

  //Add particles to state
  for (int i = 0; i < 16; i++)
    state.AddParticle(
      Coordinate(std::vector<double>{2. * (i % 4), 2. * (i / 4)}),
      Coordinate::RandomUniform(2, generator) * scale);

  std::cout << "Declaring system" << std::endl;
  //Initialize the state-energy pair (system)
  ClassicalPairwiseParticleSystem system =
    ClassicalPairwiseParticleSystem(pairwise_potential, state);

  std::cout << "Creating loggers" << std::endl;
  //Initialize data collection object
  VelocityLogger velocity_logger = VelocityLogger(system);
  RSquaredLogger r_squared_logger = RSquaredLogger(system);

  VerletIntegrator verlet_integrator = VerletIntegrator(&position_coordinate_system);

  std::cout << "Building dynamics updater" << std::endl;
  double time_step = 0.005;
  //System, solver, step_time, initial_time, use_classical_ode
  DynamicsUpdate updater = DynamicsUpdate(system, verlet_integrator, time_step, 0., true);

  updater.addLogger(&velocity_logger);
  updater.addLogger(&r_squared_logger);

  std::cout << "Simulating system" << std::endl;
  //Run dynamics simulation
  updater.RunUpdateN(3000, true);

  std::cout << "Finished simulating for problem 1" << std::endl;
  std::cout << "Outputting results" << std::endl;

  //Print results from data collection
  SaveVelocityDistribution("velocity_distribution.csv", velocity_logger);
  
  std::ofstream disp_out_file("mean_displacement_squared.csv");
  disp_out_file << r_squared_logger << std::endl;
  disp_out_file.close();
}

void Problem23()
{
  std::cout << "Starting problems 2 and 3" << std::endl;
  std::cout << "Declaring potential" << std::endl;
  LennardJonesPotential pairwise_potential = LennardJonesPotential();

  std::cout << "Declaring coordinate systems" << std::endl;
  //Initialize coordinate systems
  CoordinateBounds bounds = CoordinateBounds(
    std::vector<double>{ -0., -0. },
    std::vector<double>{ 4., 4.});

  //Limit maximum velocities
  CoordinateBounds velocity_bounds = CoordinateBounds(
    std::vector<double>{-1e6, -1e6},
    std::vector<double>{1e6, 1e6});

  BoundedEuclideanSpace momentum_coordinate_system =
    BoundedEuclideanSpace(velocity_bounds);
  FlatTorusSpace position_coordinate_system = FlatTorusSpace(bounds);

  std::cout << "Creating particle state" << std::endl;

  HamiltonianParticleState state = HamiltonianParticleState(
    &position_coordinate_system,
    &momentum_coordinate_system);

  std::cout << "Adding particles" << std::endl;

  Coordinate scale =
    Coordinate(std::vector<double>{0.001, 0.001});

  std::random_device device;
  std::mt19937_64 generator(device());

  //Add particles to state
  for (int i = 0; i < 16; i++)
    state.AddParticle(
      Coordinate(std::vector<double>{(double)(i % 4), (double)(i / 4)}),
      Coordinate::RandomUnit(2, generator) * scale);

  std::cout << "Declaring system" << std::endl;
  //Initialize the state-energy pair (system)
  ClassicalPairwiseParticleSystem system =
    ClassicalPairwiseParticleSystem(pairwise_potential, state);

  double initial_temperature;

  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(false);

  int initial_iterations = 5000;
  int burn_in = 3000;
  {
    std::cout << "Creating loggers" << std::endl;
    //Initialize data collection object
    TemperatureLogger temperature_logger = TemperatureLogger(system);
    RSquaredLogger r_squared_logger = RSquaredLogger(system);
    PositionLogger position_logger = PositionLogger(system);

    std::cout << "Building dynamics updater" << std::endl;
    double time_step = 0.005;
    //System, solver, step_time, initial_time, use_classical_ode
    DynamicsUpdate updater = DynamicsUpdate(system, integrator, time_step, 0., true);

    std::cout << "Simulating system" << std::endl;
    std::cout << "Burning in" << std::endl;
    //Run dynamics simulation
    updater.RunUpdateN(burn_in, true);

    updater.addLogger(&temperature_logger);
    updater.addLogger(&r_squared_logger);
    updater.addLogger(&position_logger);

    std::cout << "Running main iterations" << std::endl;
    updater.RunUpdateN(initial_iterations - burn_in, true);

    std::cout << "Finished simulating" << std::endl;
    std::cout << "Outputting results" << std::endl;
    //Print results from data collection
    double mean_temperature = 0.;
    for (int i = 0; i < temperature_logger.getLogCount(); i++)
      mean_temperature += temperature_logger.getTemperatures().at(i);
    mean_temperature /= temperature_logger.getTemperatures().size();

    std::cout << "Mean temperature: " << mean_temperature << std::endl;
    initial_temperature = mean_temperature;

    std::ofstream disp_out_file("mean_displacement_squared_solid.csv");
    disp_out_file << r_squared_logger << std::endl;
    disp_out_file.close();

    std::ofstream pos_out_file("positions_solid.csv");
    pos_out_file << position_logger << std::endl;
    pos_out_file.close();
  }

  MetropolisDynamicsUpdate<MetropolisNVTUpdate> updater =
    MetropolisDynamicsUpdate<MetropolisNVTUpdate>(system, integrator, 0.005, 0., true);
  updater.metropolis.setMeanSquaredStep(1.);

  TemperatureLogger stoch_temperature_logger = TemperatureLogger(system);
  RSquaredLogger stoch_r_squared_logger = RSquaredLogger(system);
  updater.addLogger(&stoch_temperature_logger);
  updater.addLogger(&stoch_r_squared_logger);

  std::cout << "Simulating melting process" << std::endl;
  for (int i = 0; i < 40; i++)
  {
    updater.metropolis.setT(initial_temperature + 0.1 * i);
    std::cout << "Simulating at temperature " << initial_temperature + 0.1 * i << std::endl;

    updater.RunUpdateN(500);
  }

  std::cout << "Saving data" << std::endl;
  std::ofstream temp_out_file("melting_temperatures.csv");
  temp_out_file << stoch_temperature_logger << std::endl;
  temp_out_file.close();

  std::ofstream disp_out_file("mean_displacement_squared_melting.csv");
  disp_out_file << stoch_r_squared_logger << std::endl;
  disp_out_file.close();
}

int main()
{
  Problem1();

  Problem23();

  return 0;
}

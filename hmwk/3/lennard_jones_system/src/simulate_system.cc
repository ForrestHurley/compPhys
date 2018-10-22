
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
  LennardJonesPotential pairwise_potential = LennardJonesPotential();
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(false);

  //Initialize coordinate systems
  std::vector<double> bounds{ 10., 10. };
  FlatTorusSpace position_coordinate_system = FlatTorusSpace(bounds);
  EuclideanSpace momentum_coordinate_system = EuclideanSpace(bounds.size());

  //Create particle state
  HamiltonianParticleState state = HamiltonianParticleState(
    &position_coordinate_system,
    &momentum_coordinate_system);

  //Add particles to state
  for (int i = 0; i < 16; i++)
    state.AddStationaryParticle(
      Coordinate(std::vector<double>{i % 4, i / 4}));

  //Initialize the state-energy pair (system)
  ClassicalPairwiseParticleSystem system =
    ClassicalPairwiseParticleSystem(pairwise_potential, state);

  //Initialize data collection object
  EnergyLogger energy_logger = EnergyLogger(system);


  //System, solver, step_time, initial_time, use_classical_ode
  DynamicsUpdate updater = DynamicsUpdate(system, integrator, 0.01, 0., false);

  updater.addLogger(&energy_logger);

  //Run dynamics simulation
  updater.RunUpdateForDuration(1.);

  //Print results from data collection
  std::cout << energy_logger << std::endl;

  return 0;
}

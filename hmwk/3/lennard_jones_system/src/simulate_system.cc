
#include "hamiltonian_particle_state.h"
#include "dynamics_update.h"
#include "classical_pairwise_particle_system.h" 
#include "lennard_jones_potential.h"
#include "integ_runge_kutta.h"
#include "flat_torus_space.h"
#include "euclidean_space.h"

int main()
{
  LennardJonesPotential pairwise_potential = LennardJonesPotential();
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(false);

  std::vector<double> bounds{ 10., 10. };
  FlatTorusSpace position_coordinate_system = FlatTorusSpace(bounds);
  EuclideanSpace momentum_coordinate_system = EuclideanSpace(bounds.size());

  HamiltonianParticleState state = HamiltonianParticleState(
    &position_coordinate_system,
    &momentum_coordinate_system);

  //Add particles to state

  //Initialize the state-energy pair (system)
  ClassicalPairwiseParticleSystem system =
    ClassicalPairwiseParticleSystem(pairwise_potential, state);

  //Initialize data collection object

  //System, solver, step_time, initial_time, use_classical_ode
  DynamicsUpdate updater = DynamicsUpdate(system, integrator, 0.01, 0., false);

  //Run dynamics simulation
  updater.RunUpdateN(10000);

  //Print results from data collection

  return 0;
}

#include "dynamics_update.h"

DynamicsUpdate::ClassicalDynamicsODE::ClassicalDynamicsODE(
  ClassicalParticleSystem& system, bool preserve_state) :
  ODEInterface(2),
  system(system), preserve_state(preserve_state) {}

std::vector<double> DynamicsUpdate::ClassicalDynamicsODE::CalculateHighestDerivative(
  const std::vector< std::vector<double> > &values, double time)
{
  std::vector<double> positions, momenta;
  positions.reserve(values.size());

  for(int i = 0; i < values.size(); i++)
  {
    assert(values.at(i).size() == 2);
    positions.push_back(values.at(i).at(0));
  }

  HamiltonianParticleState& state = 
    static_cast<HamiltonianParticleState&>(system.getState());

  //Save the current state to be reset after partial derivative calculations if necessary
  std::vector<double> temp_positions;
  if (preserve_state)
    temp_positions = DynamicsUpdate::toVector(state.getPositions());

  DynamicsUpdate::fromVector(state.getPositions(), positions);

  std::vector<Coordinate> position_partial = system.getPositionPartial();

  //restore the state if necessary
  if(preserve_state)
    DynamicsUpdate::fromVector(state.getPositions(), temp_positions);

  std::vector<double> position_double_vect;
  position_double_vect.reserve(values.size());

  for (int i = 0; i < position_partial.size(); i++)
  {
    position_double_vect.insert(position_double_vect.end(),
      position_partial.at(i).asVector().begin(), position_partial.at(i).asVector().end());
  }

  assert(position_double_vect.size() == values.size());

  //multiply position partial by negative 1
  for (int i = 0; i < values.size(); i++)
    position_double_vect.at(i) *= -1.;

  return position_double_vect;
}

DynamicsUpdate::DynamicsODE::DynamicsODE(
  HamiltonianParticleSystem& system, bool preserve_state) :
  ODEInterface(1),
  system(system), preserve_state(preserve_state) {}

std::vector<double> DynamicsUpdate::DynamicsODE::CalculateHighestDerivative(
  const std::vector< std::vector<double> > &values, double time)
{
  int particle_count = values.size() / 2;
  assert(particle_count * 2 == values.size());

  std::vector<double> positions, momenta;
  positions.reserve(particle_count);
  momenta.reserve(particle_count);

  for(int i = 0; i < particle_count; i++)
  {
    assert(values.at(i).size() == 1);
    positions.push_back(values.at(i).at(0));

    assert(values.at(i + particle_count).size() == 1);
    momenta.push_back(values.at(i + particle_count).at(0));
  }

  HamiltonianParticleState& state = 
    static_cast<HamiltonianParticleState&>(system.getState());

  //Save the current state to be reset after partial derivative calculations if necessary
  std::vector<double> temp_positions, temp_momenta;
  if (preserve_state)
    temp_positions = DynamicsUpdate::toVector(state.getPositions());
    temp_momenta = DynamicsUpdate::toVector(state.getMomenta());

  DynamicsUpdate::fromVector(state.getPositions(), positions);
  DynamicsUpdate::fromVector(state.getMomenta(), momenta);

  //calculate the position and momentum partial derivatives of energy
  std::vector<Coordinate> position_partial = system.getPositionPartial();
  std::vector<Coordinate> momentum_partial = system.getMomentumPartial();

  //restore the state if necessary
  if(preserve_state)
    DynamicsUpdate::fromVector(state.getPositions(), temp_positions);
    DynamicsUpdate::fromVector(state.getMomenta(), temp_momenta);

  assert(position_partial.size() == momentum_partial.size());

  std::vector<double> position_double_vect, momentum_double_vect;
  position_double_vect.reserve(particle_count);
  momentum_double_vect.reserve(particle_count * 2); 
  // Later momentum_double_vect is going to have position_double_vect appended to it

  for (int i = 0; i < particle_count; i++)
  {
    assert(position_partial.at(i).dimension == momentum_partial.at(i).dimension);

    position_double_vect.insert(position_double_vect.end(),
      position_partial.at(i).asVector().begin(), position_partial.at(i).asVector().end());
    momentum_double_vect.insert(momentum_double_vect.end(),
      momentum_partial.at(i).asVector().begin(), momentum_partial.at(i).asVector().end());
  }

  assert(position_double_vect.size() == particle_count);
  assert(momentum_double_vect.size() == particle_count);

  //multiply position partial by negative 1
  for (int i = 0; i < particle_count; i++)
    position_double_vect.at(i) *= -1.;

  //Using the momentum vector as the final output vector
  momentum_double_vect.insert(momentum_double_vect.end(),
    position_double_vect.begin(), position_double_vect.end());

  return momentum_double_vect;
}

DynamicsUpdate::DynamicsUpdate(HamiltonianParticleSystem& system, ODESolver& solver, double step_time, double initial_time) :
  BasicUpdate(system), solver(solver), step_time(step_time), total_time(initial_time), use_classical_ode(false)
{
  ode = new DynamicsODE(system);
  solver.setDifferentialEquation(ode);
}

DynamicsUpdate::DynamicsUpdate(ClassicalParticleSystem& system, ODESolver& solver,
  double step_time, double initial_time, bool use_classical_ode) :
  BasicUpdate(system), solver(solver),
  step_time(step_time), total_time(initial_time), use_classical_ode(use_classical_ode)
{
  if (use_classical_ode)
    ode = new ClassicalDynamicsODE(system);
  else
    ode = new DynamicsODE(system);
  solver.setDifferentialEquation(ode);
}

DynamicsUpdate::~DynamicsUpdate()
{
  delete ode;
}

void DynamicsUpdate::RunUpdate()
{
  //This function is almost entirely converting to the correct form for the ODE Solver
  //TODO: Consider refactoring so that this is less necessary

  HamiltonianParticleSystem& hamiltonian_system = static_cast<HamiltonianParticleSystem&>(system);

  HamiltonianParticleState& state =
    static_cast<HamiltonianParticleState&>(system.getState());

  std::vector<double> position_vector = 
    DynamicsUpdate::toVector(state.getPositions());
  std::vector<double> momentum_vector = 
    DynamicsUpdate::toVector(state.getMomenta());

  int position_count = position_vector.size();

  std::vector< std::vector<double> > state_vector;
  state_vector.reserve(position_count);
  for (int i = 0; i < position_count; i++)
    state_vector.push_back(std::vector<double>{position_vector.at(i), momentum_vector.at(i)});

  //Actually calling the code to update the state by one step
  solver.EvolveState(state_vector, step_time, 1, total_time);
  total_time += step_time;

  position_vector.clear();
  momentum_vector.clear();

  assert(position_count == state_vector.size());
  for (int i = 0; i < position_count; i++)
  {
    position_vector.push_back(state_vector.at(i).at(0));
    momentum_vector.push_back(state_vector.at(i).at(1));
  }

  DynamicsUpdate::fromVector(state.getPositions(), position_vector);
  DynamicsUpdate::fromVector(state.getMomenta(), momentum_vector);
}

std::vector<double> DynamicsUpdate::toVector(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& state_variables)
{
  std::vector<double> out;
  out.reserve(state_variables.size()); //It should be at least this big

  for (auto single_point : state_variables)
  {
    for(double single_dimension : single_point->getCoordinate().asVector())
      out.push_back(single_dimension);
  }

  return out;
}

void DynamicsUpdate::fromVector(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& state_variables,
  const std::vector<double>& new_state)
{
  unsigned int vector_index = 0;

  for (auto single_point : state_variables)
  {
    std::vector<double> new_coordinate_vector(
      new_state.begin() + vector_index,
      new_state.begin() + vector_index + single_point->getDimension());

    single_point->setCoordinate(
      Coordinate(new_coordinate_vector));

    vector_index += single_point->getDimension();
  }

  assert(vector_index == new_state.size());
}


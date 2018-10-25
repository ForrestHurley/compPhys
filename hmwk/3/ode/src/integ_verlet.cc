
#include "integ_verlet.h"
#include "integ_runge_kutta.h"
#include "euclidean_space.h"

VerletIntegrator::VerletIntegrator(unsigned int dimension) : 
  initial_solver(*new RungeKuttaIntegrator()),
  space(new EuclideanSpace(dimension)),
  owns_space(true) {}

VerletIntegrator::VerletIntegrator(SmoothCoordinateSpace* space) :
  initial_solver(*new RungeKuttaIntegrator()),
  space(space),
  owns_space(false) {}

VerletIntegrator::VerletIntegrator(ODEInterface *differential_equation,
  unsigned int dimension) : 
  ODESolver(differential_equation), 
  initial_solver(*new RungeKuttaIntegrator(differential_equation)),
  space(new EuclideanSpace(dimension)),
  owns_space(true) {}

VerletIntegrator::VerletIntegrator(ODEInterface *differential_equation,
  SmoothCoordinateSpace* space) :
  ODESolver(differential_equation),
  initial_solver(*new RungeKuttaIntegrator(differential_equation)),
  space(space),
  owns_space(false) {}

VerletIntegrator::VerletIntegrator(
  ODEInterface *differential_equation, 
  SmoothCoordinateSpace* space,
  ODESolver& initial_solver) : 
  ODESolver(differential_equation), 
  initial_solver(initial_solver),
  space(space),
  owns_space(false) {}

void VerletIntegrator::InitializeFirstState(std::vector<double> &state,
  double time_step, double initial_time)
{
  std::vector< std::vector<double> > manip_vect;
  manip_vect.push_back(state);

  InitializeFirstState(manip_vect, time_step, initial_time);
}

void VerletIntegrator::InitializeFirstState(std::vector< std::vector<double> > &state,
  double time_step, double initial_time)
{
  initial_solver.setDifferentialEquation(differential_equation);

  previous_state = StateToPositions(state);
  initial_solver.EvolveState(state, time_step, 1, initial_time);
}

std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>* 
  VerletIntegrator::StateToPositions(
  const std::vector< std::vector<double> >& state)
{
  const unsigned int dimension = space->getDimension();
  unsigned int point_count = state.size() / dimension;
  assert(point_count * dimension == state.size());

  std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>* out = 
    new std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>();

  for (unsigned int i = 0; i < point_count; i++)
  {
    std::vector<double> point_data;
    point_data.reserve(dimension);
    for (unsigned int j = 0; j < dimension; j++)
      point_data.push_back(state.at(i * dimension + j).at(0));

    const Coordinate coord = Coordinate(point_data);

    out->push_back(
      &space->CreatePoint(coord));
  }

  return out;
}

void VerletIntegrator::DeletePoints(
  const std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >& points)
{
  for (SmoothCoordinateSpace::SmoothCoordinatePoint* point : points)
    space->DestroyPoint(point);
}

//TODO: Modify to work with flat torus spaces
void VerletIntegrator::StepState(std::vector< std::vector<double> > &state, double time_step, double time) 
{
  std::vector<double> acceleration =
    differential_equation->CalculateHighestDerivative(state, time);

  std::vector< std::vector<double> > out;
  out.reserve(state.size());

  std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >* state_points =
    StateToPositions(state);

  unsigned int state_index = 0;
  for (unsigned int i = 0; i < state_points->size(); i++)
  {
    std::vector<double> out_row;

    const Coordinate displacement =
      space->DisplacementVector(
        *state_points->at(i), *previous_state->at(i));

    const std::vector<double> disp_vector =
      displacement.asVector();
    const std::vector<double> position_vect =
      state_points->at(i)->getCoordinate().asVector();

    for (unsigned int j = 0; j < disp_vector.size(); j++)
    {
      //position calculation
      out_row.push_back(
        position_vect.at(j) + 
        disp_vector.at(j) +
        acceleration.at(state_index) * time_step * time_step);

      //velocity calculation O(dt) error (could be better, but takes more work)
      out_row.push_back(
        disp_vector.at(j) / time_step);
        
      out.push_back(out_row);
      state_index++;
    }
  }

  std::vector< SmoothCoordinateSpace::SmoothCoordinatePoint* >* temp_points = 
    previous_state;
  previous_state = state_points;

  DeletePoints(*temp_points);
  delete temp_points;

  state = out;
}

void VerletIntegrator::EvolveState(std::vector< std::vector<double> > &state, double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  InitializeFirstState(state, step_size, initial_time);
  ODESolver::EvolveState(state,
    total_time - step_size, number_of_steps - 1, initial_time + step_size);
}

void VerletIntegrator::EvolveState(std::vector<double> &state, double total_time, int number_of_steps, double initial_time) 
{
  double step_size = total_time / number_of_steps;

  InitializeFirstState(state, step_size, initial_time);
  ODESolver::EvolveState(state,
    total_time - step_size, number_of_steps - 1, initial_time + step_size);
}


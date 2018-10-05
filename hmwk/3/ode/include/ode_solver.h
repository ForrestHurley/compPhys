
#include <vector>

class ode_solver
{
private:
  const ode_interface *differential_equation;
public:
  ode_solver(ode_interface *differential_equation); 

  virtual void step_state(std::vector< std::vector<double> > &state, double time_step) = 0;
  virtual void step_state(std::vector<double> &state, double time_step);

  virtual void evolve_state(std::vector< std::vector<double> > &state, double total_time, int number_of_steps);
  virtual void evolve_state(std::vector<double> &state, double total_time, int number_of_steps);
};

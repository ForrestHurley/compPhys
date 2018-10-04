
class ode_interface
{
public:
  const int degree;
  
  ode_interface(int degree);

  virtual void update_values(std::vector<double> &values, double time_step) = 0;
  virtual void update_values(std::vector<std::vector<double>> &values, double time_step);
}

class ode_solver
{
public:
  ode_solver(ode_interface *differential_equation); 
}

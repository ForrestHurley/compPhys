#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>
#include "monte_carlo_object.h"

class monte_carlo
{
private:
    std::vector<double> hamiltonian_list;
    mc_object* working_model;    

    double beta;
    static constexpr double k = 4.3806e-23;

public:

    monte_carlo(double temperature = 10.);
    monte_carlo(mc_object* model, double temperature = 10.);

    void set_mc_object(mc_object* model);

    void set_beta(double new_beta);
    double get_beta();
    void set_temperature(double new_temperature);
    double get_temperature();

    std::vector<double> get_hamiltonian_list();
    void run_iterations(int iterations, bool verbose = false);

};

#endif

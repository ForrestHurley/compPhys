
#include "ising_model.h"
#include "monte_carlo.h"
#include <iostream>
#include <math.h>

void iterate_model(ising_model& model, double min_t = 0.2, double max_t = 5, double t_steps = 25)
{
    double t;
    double hamiltonian;
    double weight;
    double spin;

    std::cout.precision(5);
    std::cout << "Iterating Model with dimension " << model.dimension << " and length " << model.length << std::endl;
    std::cout << "T,<H>/N,C,<|s|>" << std::endl;

    double t_step_size = (max_t - min_t) / (t_steps - 1);
    for (int i = 0; i < t_steps; i++)
    {
        t = (i * t_step_size + min_t);

        double weight_sum = 0;
        double h_exp = 0;
        double h_sqr_exp = 0;

        double avg_abs_spin_exp = 0;

        model.zero_model();

        for (; !model.pop_wrapped(); model++)
        {
            hamiltonian = model.get_hamiltonian();
            weight = exp( - 1. / t * 
                hamiltonian );
            spin = model.average_spin();            

            weight_sum += weight;
            h_exp += weight * hamiltonian;
            h_sqr_exp += weight * hamiltonian * hamiltonian;
            avg_abs_spin_exp += abs(weight * spin); //Later use kde
        } 

        h_exp /= weight_sum;
        h_sqr_exp /= weight_sum;
        avg_abs_spin_exp /= weight_sum;

        double u = h_exp / model.size;
        double c = (h_sqr_exp - h_exp * h_exp) / (t * t * model.size);

        std::cout << std::fixed << t << "," << u << "," << c << "," << avg_abs_spin_exp << std::endl;
    }
}

void mcmc_evolve_model(ising_model& model, int iterations = 200000, int burn_in = 5000, double min_t = 0.2, double max_t = 5, double t_steps = 25)
{
    model.init_random_state();
    monte_carlo metropolis(&model);
    double t;

    std::cout.precision(5);
    std::cout << "Walking Model with dimension " << model.dimension << " and length " << model.length << std::endl;
    std::cout << "T,<H>/N,C,<|s|>" << std::endl;

    double t_step_size = (max_t - min_t) / (t_steps - 1);
    for (int i = 0; i < t_steps; i++)
    {
        t = (i * t_step_size + min_t);

        model.reset_saved_data();
        metropolis.set_beta(1. / t);
        metropolis.run_iterations(iterations, burn_in);
        
        std::vector<double> h = model.get_hamiltonian_history();
        std::vector<double> spins = model.get_average_spins();

        double h_exp = 0;
        double h_sqr_exp = 0;
        double avg_abs_spin_exp = 0;
    
        for (unsigned int idx = 0; idx < h.size(); idx++)
        {
            h_exp += h[idx];
            h_sqr_exp += h[idx] * h[idx];
            avg_abs_spin_exp += abs(spins[idx]);
        }
        
        h_exp /= h.size();
        h_sqr_exp /= h.size();
        avg_abs_spin_exp /= h.size();

        double u = h_exp / model.size;
        double c = (h_sqr_exp - h_exp * h_exp) / (t * t * model.size);

        std::cout << std::fixed << t << "," << u << "," << c << "," << avg_abs_spin_exp << std::endl;
    }
}
int main()
{
    /*ising_model model_itr(4, 2);
    iterate_model(model_itr);
    mcmc_evolve_model(model_itr);*/

    ising_model model(10, 2);
    mcmc_evolve_model(model);


    /*ising_model model(4, 2);
    model.init_random_state();
    monte_carlo metro(&model);
    metro.set_beta(5.);
    metro.run_iterations(5000);
    
    double mean_hamiltonian = 0.;
    std::vector<double> hamiltonian_list = model.get_hamiltonian_history();

    for (double ham : hamiltonian_list)
        mean_hamiltonian += ham;
    mean_hamiltonian /= hamiltonian_list.size();

    std::cout << "<H>: " << mean_hamiltonian << std::endl;*/

    return 0;
}

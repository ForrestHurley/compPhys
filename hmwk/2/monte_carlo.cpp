#include "monte_carlo.h"
#include <math.h>
#include <random>
#include <iostream>

monte_carlo::monte_carlo(double temperature)
{
    set_temperature(temperature);    
}

monte_carlo::monte_carlo(mc_object* model, double temperature) : monte_carlo(temperature)
{
    set_mc_object(model);
}

void monte_carlo::set_mc_object(mc_object* model)
{
    working_model = model;
    hamiltonian_list = std::vector<double>();
}

void monte_carlo::set_beta(double new_beta)
{
    beta = new_beta;
}

double monte_carlo::get_beta()
{
    return beta;
}

void monte_carlo::set_temperature(double new_temperature)
{
    beta = 1. / (new_temperature * k);
}

double monte_carlo::get_temperature()
{
    return 1. / (beta * k);
}

std::vector<double> monte_carlo::get_hamiltonian_list()
{
    return hamiltonian_list;
}

void monte_carlo::run_iterations(int iterations, bool verbose)
{
    mc_object::mc_step* step = working_model->get_step();

    double last_hamiltonian = working_model->get_hamiltonian();
    double new_hamiltonian;
    double probability;

    static std::random_device rand_dev;
    static thread_local std::mt19937_64 generator(rand_dev());
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < iterations; i++)
    {
        step->random_step();
        working_model->apply_step(step);
        new_hamiltonian = working_model->get_hamiltonian();

        if(new_hamiltonian > last_hamiltonian)
        {
            probability = std::exp( - beta * (new_hamiltonian - last_hamiltonian) );

            if (probability > distribution(generator))
            {
                last_hamiltonian = new_hamiltonian;
            }
            else
            {
                step->invert_step();
                working_model->apply_step(step);
            }
        }
        else
        {
            last_hamiltonian = new_hamiltonian;
        }

        hamiltonian_list.push_back(last_hamiltonian);

        std::cout << "Last " << last_hamiltonian << std::endl;
    }
}

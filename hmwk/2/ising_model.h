#ifndef ISING_MODEL_H
#define ISING_MODEL_H

#include "monte_carlo_object.h"
#include <random>

class ising_model : mc_object
{

public:
    
    class ising_step : mc_object::mc_step
    {
    public:
        ising_step(int size);

        void invert_step() override;
        void random_step() override;

    private:
        int flip_index = 0;
        std::uniform_int_distribution<int> step_distribution;
    }

private:
    std::vector<bool> spin_list;

    const int size;

public:
    ising_model(int length = 4, int dims = 2);
    
    void init_random_state() override;

    double get_hamiltonian() override;
    void apply_step(mc_step& step) override;

    mc_step get_step() override;

    ising_model& operator++();
    ising_model operator++(int);
}

#endif

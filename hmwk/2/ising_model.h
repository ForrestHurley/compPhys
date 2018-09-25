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

    int full_recalculation_frequency = 1000;

private:
    std::vector<bool> spin_list;

    const int dimension;
    const int size;

    double hamiltonian_value;

    int steps_since_last_recalc = 0;

    ising_step last_step;

public:
    ising_model(int length = 4, int dims = 2);
    
    void init_random_state() override;

    double get_hamiltonian() override;
    void apply_step(mc_step* step) override;
    void apply_step(ising_step* step) override;

    mc_step get_step() override;

    ising_model& operator++();
    ising_model operator++(int);

private:
    int location_to_index(std::vector<int> location);
    std::vector<int> index_to_location(int index);

    void calculate_hamiltonian();
    void update_hamiltonian();
}

#endif

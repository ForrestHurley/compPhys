#ifndef ISING_MODEL_H
#define ISING_MODEL_H

#include "monte_carlo_object.h"
#include <random>

class ising_model : public mc_object
{

public:
    
    class ising_step : public mc_object::mc_step
    {
    public:
        ising_step(int size);

        void invert_step() override;
        void random_step() override;

        int get_index();

    private:
        int flip_index = 0;
        std::uniform_int_distribution<int> step_distribution;
    };

    const int length;
    const int dimension;
    const int size;

    int full_recalculation_frequency = 1000;

private:
    std::vector<bool> spin_list;

    double hamiltonian_value;

    int steps_since_last_recalc = 0;

    int last_step_index;

    ising_step working_step;
    
    std::vector<double> average_spin_list;
    std::vector<double> hamiltonian_list;
    bool wrapped_itr = false;

public:
    ising_model(int length = 4, int dims = 2);
    
    void zero_model();
    void init_random_state() override;
    void reset_saved_data();

    double get_hamiltonian() override;
    double average_spin();

    void apply_step(mc_step* step) override;
    void apply_step(ising_step* step);

    mc_step* get_step() override;

    void store_data() override;

    ising_model& operator++();
    ising_model operator++(int);
    bool pop_wrapped();

    std::vector<double> get_average_spins();
    std::vector<double> get_hamiltonian_history();

private:
    int location_to_index(std::vector<int> location);
    std::vector<int> index_to_location(int index);

    void calculate_hamiltonian();
    void update_hamiltonian();

    double single_pair_value(int first_index, int second_index);
};

#endif

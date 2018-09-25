#include "ising_model.h"
#include <limits>

ising_model::ising_step::ising_step(int size) : mc_object::mc_step()
{
    step_distribution = std::uniform_int_distribtion<int>(0, size);
}

void ising_model::ising_step::invert_step() { }

void ising_model::ising_step::random_step()
{
    static thread_local std::random_device rand_dev();
    static thread_local std::mt19937_64 generator(rand_dev);

    flip_index = step_distribution(generator); 
}

void ising_model::ising_model(int length, int dims) : dimension(dims), size((int)round(pow(length, (double)dims)))
{
    spin_list = std::vector<bool>(size);
    for (int i = 0; i < size; i++)
        spin_list[i] = false;

    calculate_hamiltonian();
}

void ising_model::init_random_state()
{
    static thread_local std::random_device rand_dev();
    static thread_local std::mt19937_64 generator(rand_dev);

    std::bernoulli_distribution distribution(0.5);

    for (int i = 0; i < size; i++)
        spin_list[i] = distribution(generator);

    calculate_hamiltonian();
}

double ising_model::get_hamiltonian()
{
    return hamiltonian_value;
}

void ising_model::apply_step(mc_step* step)
{
    apply_step(static_cast<ising_step*>(step));
}

void ising_model::apply_step(ising_step* step)
{
    spin_list[step->flip_index] ^= 1;
    last_step = *step;
    update_hamiltonian();
}

mc_step ising_model::get_step()
{
    return ising_step(size);
}

ising_model& ising_model::operator++()
{
    for (int i = 0; i < size; i++)
    {
        if (spin_list[i] == 0)
        {
            spin_list[i] = 1;
            return *this;
        }
        
        spin_list[i] = 0;
    }
}

ising_model ising_model::operator++(int)
{
    ising_model temp = *this;
    ++*this;
    return temp;
}

int ising_model::location_to_index(std::vector<int> location)
{

}

std::vector<int> ising_model::index_to_location(int index)
{

}

void ising_model::calculate_hamiltonian()
{

}

void ising_model::update_hamiltonian()
{
    if (steps_since_last_recalc > full_recalculation_frequency)
    {
        calculate_hamiltonian();
        steps_since_last_recalc = 0;
    }
    else
    {

        steps_since_last_recalc++;
    }
}

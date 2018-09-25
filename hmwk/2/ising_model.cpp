#include "ising_model.h"

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

void ising_model::ising_model(int length, int dims) : size((int)round(pow(length, (double)dims)))
{
    spin_list = std::vector<bool>(size);
    for (int i = 0; i < size; i++)
        spin_list[i] = false;
}

void ising_model::init_random_state()
{
    static thread_local std::random_device rand_dev();
    static thread_local std::mt19937_64 generator(rand_dev);

    std::bernoulli_distribution distribution(0.5);

    for (int i = 0; i < size; i++)
        spin_list[i] = distribution(generator);
}

double ising_model::get_hamiltonian()
{

}

void ising_model::apply_step(mc_step& step)
{
    spin_list[step.flip_index] ^= 1;
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

#include "ising_model.h"
#include <limits>
#include <random>
#include <iostream>

ising_model::ising_step::ising_step(int size) : mc_object::mc_step()
{
    step_distribution = std::uniform_int_distribution<int>(0, size);
}

void ising_model::ising_step::invert_step() { }

void ising_model::ising_step::random_step()
{
    static std::random_device rand_dev;
    static thread_local std::mt19937_64 generator(rand_dev());

    flip_index = step_distribution(generator); 
}

int ising_model::ising_step::get_index()
{
    return flip_index;
}

ising_model::ising_model(int length, int dims) : length(length), dimension(dims), size((int)round(pow(length, (double)dims))), working_step(size) 
{
    zero_model();
}

void ising_model::zero_model()
{
    spin_list = std::vector<bool>(size);
    for (int i = 0; i < size; i++)
        spin_list[i] = false;

    calculate_hamiltonian();
    reset_saved_data();
}

void ising_model::init_random_state()
{
    static std::random_device rand_dev;
    static thread_local std::mt19937_64 generator(rand_dev());

    std::bernoulli_distribution distribution(0.5);

    for (int i = 0; i < size; i++)
        spin_list[i] = distribution(generator);

    calculate_hamiltonian();
    reset_saved_data();
}

void ising_model::reset_saved_data()
{
    average_spin_list = std::vector<double>();
    hamiltonian_list = std::vector<double>();
}

double ising_model::get_hamiltonian()
{
    return hamiltonian_value;
}

double ising_model::average_spin()
{
    int sum = 0;
    for (int spin : spin_list)
        sum += spin;
    double average = (double)sum / spin_list.size();
    
    //Convert from 0, 1 to -1, 1
    average = 2. * average - 1.;

    return average;
}

void ising_model::apply_step(mc_step* step)
{
    apply_step(static_cast<ising_step*>(step));
}

void ising_model::apply_step(ising_step* step)
{
    const int index = step->get_index();
    spin_list[index] = !spin_list[index];
    last_step_index = index;
    calculate_hamiltonian();//update_hamiltonian();
}

mc_object::mc_step* ising_model::get_step()
{
    return &working_step;
}

void ising_model::store_data()
{   
    average_spin_list.push_back(average_spin());
    hamiltonian_list.push_back(get_hamiltonian());
}

ising_model& ising_model::operator++()
{
    for (int i = 0; i < size; i++)
    {
        if (spin_list[i] == 0)
        {
            spin_list[i] = 1;
            calculate_hamiltonian();
            return *this;
        }
        
        spin_list[i] = 0;
    }
    calculate_hamiltonian();
    wrapped_itr = true;
    return *this;
}

ising_model ising_model::operator++(int)
{
    ising_model temp = *this;
    ++*this;
    return temp;
}

bool ising_model::pop_wrapped()
{
    bool out = wrapped_itr;
    wrapped_itr = false;
    return out;
}

std::vector<double> ising_model::get_average_spins()
{
    return average_spin_list;
}

std::vector<double> ising_model::get_hamiltonian_history()
{
    return hamiltonian_list;
}

int ising_model::location_to_index(std::vector<int> location)
{
    int index = 0;
    for (int i = dimension - 1; i >= 0; i--)
    {
        index *= length;
        index += (location[i] + length) % length;
    }
    return index;
}

std::vector<int> ising_model::index_to_location(int index)
{
    std::vector<int> location(dimension);
    for (int i = 0; i < dimension; i++)
    {
        location[i] = index % length;
        index /= length;
    }
    return location;
}

void ising_model::calculate_hamiltonian()
{
    double hamiltonian = 0.;
    std::vector<int> index_location;    
    std::vector<int> other_location;
    int other_index;

    for (int i = 0; i < size; i++)
    {
        index_location = index_to_location(i);

        for (unsigned int j = 0; j < index_location.size(); j++)
        {
            other_location = index_location;
            other_location[j] += 1;
            other_index = location_to_index(other_location);
        
            hamiltonian += single_pair_value(i, other_index);    
        }
    }

    hamiltonian_value = hamiltonian;
}

void ising_model::update_hamiltonian()
{
    //TODO: Debug
    /*if (steps_since_last_recalc > full_recalculation_frequency)
    {
        calculate_hamiltonian();
        steps_since_last_recalc = 0;
    }
    else
    {
        std::vector<int> index_location = index_to_location(last_step_index);
        std::vector<int> other_location;
        int other_index;

        for (int i = 0; i < dimension * 2; i++)
        {
            other_location = index_location;
            other_location[i/2] += (i % 2) * 2 - 1;
            other_index = location_to_index(other_location);

            //The multiplication by 2 cancels out the previous state, before the flip
            hamiltonian_value += 2 * single_pair_value(last_step_index, other_index);
        }

        steps_since_last_recalc++;
    }*/
}

double ising_model::single_pair_value(int first_index, int second_index)
{
    const int first_value = spin_list[first_index];
    const int second_value = spin_list[second_index];
    const int first_spin = first_value * 2 - 1;
    const int second_spin = second_value * 2 - 1;

    const int energy = - (first_spin * second_spin);

    return energy;
}

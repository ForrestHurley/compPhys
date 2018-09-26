
#include "ising_model.h"
#include "monte_carlo.h"
#include <iostream>

int main()
{
    ising_model model_itr(4, 2);

    for (; !model_itr.pop_wrapped(); model_itr++);
 
    std::cout << i << " " << model_itr.get_hamiltonian() << std::endl;

    /*ising_model model(20, 2);
    model.init_random_state();
    monte_carlo metro(&model, 4e22);
    metro.run_iterations(50000);*/

    return 0;
}

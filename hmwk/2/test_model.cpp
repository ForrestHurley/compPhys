
#include "ising_model.h"
#include "monte_carlo.h"
#include <iostream>

int main()
{
    std::cout << "test" << std::endl;
    ising_model model(4, 2);
    std::cout << "test" << std::endl;
    monte_carlo metro(&model, 2);
    std::cout << "test" << std::endl;
    metro.run_iterations(10);
    return 0;
}


#include "ising_model.h"
#include "monte_carlo.h"
#include <iostream>

int main()
{
    ising_model model(4, 2);
    monte_carlo metro(&model, 4e23);
    metro.run_iterations(50);
    return 0;
}

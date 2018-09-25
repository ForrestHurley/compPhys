#ifndef MONTE_CARLO_OBJECT_H
#define MONTE_CARLO_OBJECT_H

class mc_object
{
public:

    class mc_step
    {
    public:
        virtual void invert_step();
        virtual void random_step();
    }

    virtual void init_random_state();

    virtual double get_hamiltonian();
    virtual void apply_step(mc_step* step);

    virtual mc_step get_step();
}

#endif

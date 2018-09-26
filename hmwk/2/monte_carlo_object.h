#ifndef MONTE_CARLO_OBJECT_H
#define MONTE_CARLO_OBJECT_H

class mc_object
{
public:

    class mc_step
    {
    public:
        virtual void invert_step() = 0;
        virtual void random_step() = 0;
    };

    virtual void init_random_state() = 0;

    virtual double get_hamiltonian() = 0;
    virtual void apply_step(mc_step* step) = 0;

    virtual mc_step* get_step() = 0;

    virtual void store_data() {}
};

#endif

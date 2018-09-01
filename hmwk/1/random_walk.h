#ifndef RANDOM_WALK
#define RANDOM_WALK

#include <cstddef>
#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <iomanip>
#include <ctime>

template <int N, class point_type>
class random_walk
{
private:
  std::array<point_type, N> last_location;

  template <int, class>
  class step_walk_impl { public: static void _(random_walk* p) {} };

  template <int R>
  class step_walk_impl<R, int>
  {
    public:
    static void _(random_walk* p)
    {
      //static thread_local std::random_device rd;
      static thread_local std::mt19937_64 engine(time(0));
      static thread_local std::uniform_int_distribution<int> distribution(0, R * 2 - 1);

      int random_num = distribution(engine);

      int direction = (random_num % 2) * 2 - 1;
      int dim_index = random_num / 2;

      p->last_location[dim_index] += direction;
    }
  };

  template <int R>
  class step_walk_impl<R, double>
  {
    public:
    static void _(random_walk* p)
    {
      //static thread_local std::random_device rd;
      static thread_local std::mt19937_64 engine(time(0));
      static thread_local std::normal_distribution<double> distribution(0., 1.);

      double magnitude_sqr = 0;

      std::array<double, R> step;
      for (double &dimension : step)
      {
        dimension = distribution(engine);
        magnitude_sqr += dimension*dimension;
      }

      double magnitude = sqrt(magnitude_sqr);
      for (double &dimension : step) dimension /= magnitude; 

      for (uint i = 0; i < step.size(); i++) p->last_location[i] += step[i];
    }
  };

protected:
  int steps = 0;

  void set_last_location(std::array<point_type, N> loc)
  {
    last_location = loc;
  }

public:
  int verbose = 0;

  random_walk()
  {
    for(int i = 0; i < N; i++)
      last_location[i] = 0;
  }

  virtual void step_walk() { step_walk_impl<N, point_type>::_(this); steps++; }
  
  void step_walk(int steps)
  {
    if(verbose == 0)
    {
      for(int i = 0; i < steps; i++)
        step_walk();
    }
    else
    {
      int print_interval = steps / 1000;
      if (print_interval < 1) print_interval = 1;

      for (int i = 0; i < steps; i++)
      {
        step_walk();
        if (i % print_interval == 0)
        {
          std::cout << std::setw(4) << std::fixed << std::setprecision(1) << std::setfill(' ') << "\r" 
              << (double) i / steps * 100. << " percent complete" << std::flush;
        }
      }
      std::cout << std::endl;
    }
  }

  std::array<point_type, N> get_last_location()
  {
    return last_location;
  }

  int get_total_steps()
  {
    return steps;
  }
};

template <int N, class point_type>
class random_walk_with_memory : public random_walk<N, point_type>
{
private:
  std::vector<std::array<point_type, N>> history;

protected:
  void pop_last_location()
  {
    this->set_last_location(history.back());
    history.pop_back();
    this->steps--;
  }

public:
  random_walk_with_memory() { };

  using random_walk<N, point_type>::step_walk;
  void step_walk() override
  {
    history.push_back(this->get_last_location());
    random_walk<N, point_type>::step_walk();
  }

  std::vector<std::array<point_type, N>> get_location_list()
  {
    return history;
  }

  std::array<point_type, N> get_history_at(int index)
  {
    return history[index];
  }
};

#endif

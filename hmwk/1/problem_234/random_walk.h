#ifndef RANDOM_WALK
#define RANDOM_WALK

#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

template <class point_type, int N>
class random_walk
{
public:
  using point = std::array<point_type, N>;

  int verbose = 0;

private:
  std::vector<std::array<point_type, N>> location_list;

protected:
  virtual std::array<point_type, N> generate_random_step() = 0;

  virtual bool step_forwards(int steps);
  virtual void step_backwards(int steps);

  virtual void push_point(point in_point);
  virtual void pop_point();

  virtual bool take_step(std::array<point_type, N> step);

public:

  int get_length();

  std::vector<std::array<point_type, N>> get_location_list();
  virtual std::vector<double> get_probabilities();
  std::array<point_type, N> get_single_location(int index);
  std::array<point_type, N> get_last_location();

  void make_walk(int steps, bool restart_on_failure = true);

  void write_to_file(std::string f);

  static inline point get_zero_point();

  using point_data_type = point_type;
  static const int dimensions = N;
};

template <class point_type, int N>
void random_walk<point_type, N>::push_point(random_walk<point_type, N>::point in_point)
{
  location_list.push_back(in_point);
}

template <class point_type, int N>
void random_walk<point_type, N>::pop_point()
{
  location_list.pop_back();
}

template <class point_type, int N>
bool random_walk<point_type, N>::take_step(std::array<point_type, N> step)
{
    std::array<point_type, N> new_location = get_last_location();

    for (int j = 0; j < N; j++)
      new_location[j] += step[j];

    push_point(new_location);
    return true;
}

template <class point_type, int N>
bool random_walk<point_type, N>::step_forwards(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    std::array<point_type, N> random_step = generate_random_step();
    take_step(random_step);
  }

  return true;
}

template <class point_type, int N>
void random_walk<point_type, N>::step_backwards(int steps)
{
  for (int i = 0; i < steps; i++)
    pop_point();
}

template <class point_type, int N>
void random_walk<point_type, N>::make_walk(int steps, bool restart_on_failure)
{
  push_point(get_zero_point());

  int print_interval = steps / 1000;
  if (print_interval == 0) print_interval = 1;

  if (verbose > 0)
    std::cout << std::setw(4) << std::fixed << std::setprecision(1) << std::setfill(' ');
  
  for (int i = 0; i < steps; i++)
  {
    if(verbose > 0 && get_length() % print_interval == 0)
    {
      std::cout << "\r" << (double)get_length() / steps * 100. << " percent complete" << std::flush;
    }

    if (!step_forwards(1)) //Check for failed step
    {
      if (!restart_on_failure)
      {
        if (verbose >= 1)
          std::cout << std::endl << "Ending due to a collision" << std::endl;
        return;
      }

      if (verbose >= 2)
        std::cout << std::endl << "Restarting due to a collision" << std::endl;
      int length = get_length();
      for(int j = 0; j < length - 1; j++)
        pop_point();
      i = 0;
    }
  }
}

template <class point_type, int N>
int random_walk<point_type, N>::get_length()
{
  return location_list.size();
}

template <class point_type, int N>
std::vector<std::array<point_type, N>> random_walk<point_type, N>::get_location_list()
{
  return location_list;
}

template <class point_type, int N>
std::vector<double> random_walk<point_type, N>::get_probabilities()
{
  std::vector<double> out(location_list.size());

  for(unsigned int i = 0; i < out.size(); i++)
    out[i] = 1. / N;

  return out;
}

template <class point_type, int N>
std::array<point_type, N> random_walk<point_type, N>::get_single_location(int index)
{
  return location_list.at(index);
}

template <class point_type, int N>
std::array<point_type, N> random_walk<point_type, N>::get_last_location()
{
  return location_list.back();
}

template <class point_type, int N>
void random_walk<point_type, N>::write_to_file(std::string f)
{
  std::ofstream out_file;
  out_file.open(f);

  int i = 0;

  for (point location : get_location_list())
  {
    out_file << i++;
    for (point_type dimension : location)
    {
      out_file << "," << dimension;
    }
    out_file << std::endl;
  }
}

template <class point_type, int N>
std::array<point_type, N> random_walk<point_type, N>::get_zero_point()
{
  static point zero;
  static bool initialized = false;
  if (!initialized)
    for (int i = 0; i < N; i++)
      zero[i] = 0;

  return zero;
}

#endif

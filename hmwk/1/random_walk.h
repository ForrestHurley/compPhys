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
  std::vector<point> location_list;

protected:
  virtual std::array<point_type, N> generate_random_step() = 0;

  virtual bool step_forwards(int steps);
  virtual void step_backwards(int steps);

public:
  virtual void push_point(point in_point);
  virtual void pop_point();

  int get_length();

  std::vector<point> get_location_list();
  point get_single_location(int index);
  point get_last_location();

  void make_walk(int steps);

  void write_to_file(std::string f);

  static inline point get_zero_point();
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
bool random_walk<point_type, N>::step_forwards(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    point random_step = generate_random_step();
    point new_location = get_last_location();

    for (int j = 0; j < N; j++)
      new_location[j] += random_step[j];

    push_point(new_location);
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
void random_walk<point_type, N>::make_walk(int steps)
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
      int length = get_length();
      for(int j = 0; j < length; j++)
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

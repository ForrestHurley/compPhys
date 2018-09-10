#ifndef RANDOM_WALK
#define RANDOM_WALK

template <class point_type, int N>
class random_walk
{
public:
  using point = std::array<point_type, N>

private:
  std::vector<point> location_list;

protected:
  virtual point generate_random_step();

  virtual bool step_forwards(int steps);
  virtual void step_backwards(int steps);

public:
  virtual void push_point(point in_point);
  virtual point pop_point();
  

  int get_length();

  std::vector<point> get_location_list();
  point get_single_location(int index);

  void make_walk(int steps);

  void write_to_file(std::string f);
}


template <class point_type, int N>
virtual void random_walk<point_type, N>::push_point(random_walk<class, N>::point in_point);

template <class point_type, int N>
virtual random_walk<point_type, N>::point random_walk<point_type, N>::pop_point();

template <class point_type, int N>
virtual bool random_walk<point_type, N>::step_forwards(int steps);

template <class point_type, int N>
virtual void random_walk<point_type, N>::step_backwards(int steps);

template <class point_type, int N>
void random_walk<point_type, N>::make_walk(int steps);

template <class point_type, int N>
int random_walk<point_type, N>::get_length();

template <class point_type, int N>
std::vector<random_walk<point_type, N>::point> random_walk<point_type, N>::get_location_list();

template <class point_type, int N>
random_walk<point_type, N>::point random_walk<point_type, N>::get_single_location(int index);

template <class point_type, int N>
random_walk<point_type, N>::point random_walk<point_type, N>::generate_random_step();


template <class point_type, int N>
void random_walk<point_type, N>::write_to_file(std::string f)
{
  std::ofstream out_file;
  out_file.open(f);

  int i = 0;

  for (random_walk<point_type, N>::point location : get_location_list())
  {
    out_file << i++;
    for (point_type dimension : location)
    {
      out_file << "," << dimension;
    }
    out_file << std::endl;
  }
}

#endif


#include "binned_coordinates.cc"

BinnedCoordinates::BinnedCoordinates(std::vector<int> bin_counts) : bin_counts(bin_counts) {}

BinnedCoordinates::BinnedCoordinates(const std::vector<Coordinate&>& locations, const std::vector<double>& bin_dimensions) : 
  bin_counts() {}

std::vector<int> BinnedCoordinates::getBinIndex(Coordinate& location)
{
  return std::vector<int>();
}

int BinnedCoordinates::getBinNumber(Coordinate& location)
{
  return 0;
}

std::vector<int> BinnedCoordinates::getBinCounts()
{
  return std::vector<int>();
}

int BinnedCoordinates::getTotalBins()
{
  return 0;
}

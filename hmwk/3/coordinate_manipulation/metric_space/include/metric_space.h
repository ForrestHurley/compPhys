#ifndef METRIC_SPACE_H
#define METRIC_SPACE_H

#include <unordered_set>

class MetricSpace
{
public:
  class MetricPoint
  {
  private:
    const MetricSpace* space;

  public:
    MetricPoint(MetricSpace* space) : space(space) {}

    virtual ~MetricPoint() {}

    const MetricSpace* getSpace() const { return space; } 
  };

private:
  std::unordered_set<MetricPoint*> point_set;

public:
  virtual ~MetricSpace()
  {
    for (MetricPoint* point : point_set) delete point;
  }

  virtual double Distance(const MetricPoint& A, const MetricPoint& B) const = 0;

  virtual const MetricPoint& getOrigin() const = 0;
  virtual void addPoint(MetricPoint* point) 
    { point_set.insert(point); }
  virtual void removePoint(MetricPoint* point) 
    { delete point; point_set.erase(point); }
};

#endif

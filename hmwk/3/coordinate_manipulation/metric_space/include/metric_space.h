#ifndef METRIC_SPACE_H
#define METRIC_SPACE_H

class MetricSpace
{
public:
  class MetricPoint
  {
  private:
    const MetricSpace* space;

  public:
    MetricPoint(MetricSpace* space) : space(space) {}

    virtual ~MetricPoint() = default;

    const MetricSpace* getSpace() const { return space; } 
  };

  virtual double Distance(const MetricPoint& A, const MetricPoint& B) const = 0;

  virtual const MetricPoint& getOrigin() const = 0;
};

#endif

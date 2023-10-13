// header-start
////////////////////////////////////////////////////////////////////////////////
// \project   none
//
// \file      util.h
//
// \brief     include file with util goodies
//
// \legal     Copyright (c) 2023
//
// \author    Bernard Plessier
//
//
////////////////////////////////////////////////////////////////////////////////
// header-end

#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <QPointF>

namespace Util {

//
// class with a functor to linearly interpolate
// a y value for a given x value
// if |x0 - x1| == 0 => vertical line
// we return y0
//
//     |
// y0  =   ...
//     |      ....
// y1  =          ....
//     |
//    -----+----------+---------
//       x0           x1
//
//  (y - y0) = (y1 - y0)*(x - x0)/(x1 - x0)
//



class LinearInterpolator {
private:
  double x0_;
  double x1_;
  double y0_;
  double y1_;
  double slope_;

public:
  LinearInterpolator() {
    x0_ = 0.0;
    x1_ = 1.0;
    y0_ = 0.0;
    y1_ = 1.0;
    slope_ = 1.0;
  }

  LinearInterpolator(double x0, double x1, double y0, double y1)
    : x0_{x0}, x1_{x1}, y0_{y0}, y1_{y1}
  {
    if (std::abs(x0 -x1) < 1e-6) {
      throw std::invalid_argument("cannot have x0 too close to x1");
    }
    slope_ = (y1_ - y0_) / (x1_ - x0_);
  }

  LinearInterpolator(const QPointF& p0, const QPointF& p1) :
    LinearInterpolator(p0.x(), p1.x(), p0.y(), p1.y())
  {
  }

  // for pixel to world
  double operator()(int x)
  {
    return ((static_cast<double>(x) - x0_) * slope_) + y0_;
  }

  double operator()(double x)
  {
    return ((x - x0_) * slope_) + y0_;
  }

};

//
// Clamp class functor
//
template<typename tpl_t>
class Clamp {
private:
  int min_;
  int max_;
public:
  int operator()(tpl_t value) {
    int tmp = static_cast<int>(value);
    return (tmp < min_) ? min_ : ((tmp > max_) ? max_ : tmp);
  }
  Clamp(int min, int max) : min_{min}, max_{max} {
  }
};

//
// Commify class functor
// thousand digit separator
// 1234 => 1,234
//

class Commify {
private:
  std::string str_;
  void insert_separator(char c) {
    size_t pos = str_.length() - 3;
    while(pos > 0) {
      str_.insert(pos, 1, c);
      pos -= 3;
    }
  }
public:
  explicit Commify(int value) {
    std::ostringstream ss;
    ss << value;
    str_ = ss.str();
    insert_separator(',');
  }
  friend std::ostream& operator<<(std::ostream &os, const Commify &c) {
    os << c.str_;
    return os;
  }
};

}  // namespace 


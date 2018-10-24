/*
  Based on cangle.h @SparQ https://github.com/dwolter/SparQ
*/

#ifndef ANGLE_H
#define ANGLE_H

#include <iostream>

class Angle {
public:
  Angle();
  Angle(const float);
  ~Angle();

  float get() const;
  void set(const float rad);
  float diff(const Angle&);

  Angle operator+(const Angle&) const;
  Angle operator-(const Angle&) const;

private:
  float rad;

};


#endif

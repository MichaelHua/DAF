/*
  Revised from point.h @SparQ https://github.com/dwolter/SparQ
*/

#ifndef ORI_POINT_H
#define ORI_POINT_H

#include <math.h>
#include <iostream>

using namespace std;

class OriPoint {

  float x;
  float y;
  float anchor;

public:
  OriPoint();
  OriPoint(const float, const float, const float);
  OriPoint(const OriPoint&);
  ~OriPoint();

  const float getX(void) const;
  const float getY(void) const;

  const float getANCHOR(void) const;
  const float getAnchorAngle(void) const;

  void setX(const float);
  void setY(const float);

  void setANCHOR(const float);
  void rotateANCHOR(const float); // counter-clockwise

  void shift(const OriPoint&);
  void shift(const float, const float);

  void rotate(const float); // rotate counter-clocksiwse
  void rotate(const float, const OriPoint&);

  string toString(void);

  const OriPoint operator+(const OriPoint&) const;
  const OriPoint operator-(const OriPoint&) const;
  const bool samePos(const OriPoint&) const;

  const float GetAngleTo(const OriPoint&) const;

};

#endif

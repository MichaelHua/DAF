/*
  Based on point.h @SparQ https://github.com/dwolter/SparQ
*/

#include "ori_point.h"
#include "global.h"
#include "angle.h"
#include "rel_util.h"

#include <math.h>
#include <iostream>

using namespace std;

// zero anchor defined in DAF is like (0, 1) in 2-D coordinates.
const float ABSO_ANCHOR_ANGLE = config::ABSO_ANCHOR_ANGLE;


OriPoint::OriPoint() {
  x = 0.0;
  y = 0.0;
  anchor = 0.0;
}

OriPoint::OriPoint(const float _x, const float _y, const float _anchor) {
  x = _x;
  y = _y;
  anchor = norm(_anchor);
}

OriPoint::OriPoint(const OriPoint &p) {
  x = p.getX();
  y = p.getY();
  anchor = norm(p.getANCHOR());
}

OriPoint::~OriPoint() {}

const float OriPoint::getX(void) const {
  return x;
}

const float OriPoint::getY(void) const {
  return y;
}

const float OriPoint::getANCHOR(void) const {
  return norm(anchor);
}

const float OriPoint::getAnchorAngle(void) const {
  return norm(anchor + ABSO_ANCHOR_ANGLE);
}

void OriPoint::setX(const float _x) {
  x = _x;
}

void OriPoint::setY(const float _y) {
  y = _y;
}

void OriPoint::setANCHOR(const float _anchor) {
  anchor = norm(_anchor);
}

void OriPoint::shift(const OriPoint &op)
{
  x += op.getX();
  y += op.getY();
}

void OriPoint::shift(const float dx, const float dy)
{
  x += dx;
  y += dy;
}

void OriPoint::rotate(const float angle) {
  static float sinus;
  static float cosinus;
  static float x_tmp;

  sinus = sin(angle);
  cosinus = cos(angle);

  x_tmp = x * cosinus - y * sinus;
  y = x * sinus + y * cosinus;
  x = x_tmp;
}

void OriPoint::rotate(const float angle, const OriPoint &center) {
  shift(-center.getX(), -center.getY());
  rotate(angle);
  shift(center.getX(), center.getY());
}

string OriPoint::toString(void) {
  return "x: " + to_string(x) + " y: " + to_string(y) + " anchor: "
    + to_string(anchor);
}

const OriPoint OriPoint::operator+(const OriPoint &p2) const {
  OriPoint p(x + p2.getX(), y + p2.getY(), 0.0);
  return p;
}

const OriPoint OriPoint::operator-(const OriPoint &p2) const {
  OriPoint p(x - p2.getX(), y - p2.getY(), 0.0);
  return p;
}

const bool OriPoint::samePos(const OriPoint &p2) const {
  return ((x == p2.getX()) && (y == p2.getY()));
}

const float OriPoint::GetAngleTo(const OriPoint &p2) const
{
  return norm(atan2f(p2.getY() - y, p2.getX() - x));
}

void OriPoint::rotateANCHOR(const float delta) {
  anchor = norm(anchor + delta);
}

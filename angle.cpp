#include "angle.h"
#include "global.h"
#include "rel_util.h"

#include <math.h>
#include <iostream>

Angle::Angle() {
   rad = 0.0;
}

Angle::Angle(const float _rad) {
  rad = norm(_rad);
}

Angle::~Angle() {}

float Angle::get() const {
  return norm(rad);
}

void Angle::set(const float _rad) {
  rad = norm(_rad);
}

float Angle::diff(const Angle &a2) {
  return norm(rad - a2.get());
}

Angle Angle::operator+(const Angle &a2) const {
  return Angle(rad + a2.get());
}

Angle Angle::operator-(const Angle &a2) const {
  return Angle(rad - a2.get());
}

#ifndef TYPE_PARTIE_H
#define TYPE_PARTIE_H

#include <iostream>

int TypePartie;

std::istream& operator>>(std::istream& is, TypePartie& tp) {
  int input;
  is >> input;
  if (input == 0) {
    tp = SIMPLE;
  } else if (input == 1) {
    tp = DOUBLE;
  } else {
    is.setstate(ios_base::failbit);
  }
  return is;
}

#endif // TYPE_PARTIE_H
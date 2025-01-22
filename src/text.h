#pragma once

#include "ofMain.h"

class Text {
 private:
  ofTrueTypeFont font;

 public:
  void setup(string _text, int _r, int _g, int _b);
  void update(string _text);
  void draw();

  string text;
  int r, g, b;
};
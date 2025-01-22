#include "text.h"

void Text::setup(string _text, int _r, int _g, int _b) {
  text = _text;
  r = _r;
  g = _g;
  b = _b;

  font.load("roboto.ttf", 72);
}

void Text::update(string _text) { text = _text; }

void Text::draw() {
  ofSetColor(r, g, b);

  float w = font.stringWidth(text), h = font.stringHeight(text);
  float x = ofGetWidth() / 2 - w / 2, y = ofGetHeight() / 2 + h / 2;
  font.drawString(text, x, y);
}
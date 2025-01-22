#pragma once

#include "ofMain.h"
#include "text.h"

class ofApp : public ofBaseApp {
 public:
  void setup() override;
  void update() override;
  void draw() override;

  void mousePressed(int x, int y, int button) override;

  ofSoundPlayer timerSound;
  ofSoundPlayer failedSound;

  ofSerial Arduino;

  Text title;
  Text time;
  Text success;
  Text failed;
};

#define SERIALPORT "/dev/cu.usbmodem101"
#define BAUDRATE 9600

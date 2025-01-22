#include "ofApp.h"

const int numCables = 3;
int correctCable;
int status;

float startTime;
int timerDuration;

bool isStarted;
bool isTimerActive;

//--------------------------------------------------------------
void ofApp::setup() {
  Arduino.setup(SERIALPORT, BAUDRATE);

  ofBackground(200);
  ofSetFrameRate(60);

  title.setup("Click to start", 0, 0, 0);
  time.setup("0", 220, 0, 0);
  success.setup("Success", 0, 200, 0);
  failed.setup("Failed", 200, 0, 0);

  status = 0;

  correctCable = int(ofRandom(0, numCables));

  timerDuration = 5;
  startTime = 0;
  isStarted = false;
  isTimerActive = false;

  timerSound.load("timer.mp3");
  timerSound.setLoop(true);
  failedSound.load("failed.mp3");
}

//--------------------------------------------------------------
void ofApp::update() {
  // タイムオーバー
  if (isTimerActive) {
    float elapsedTime = ofGetElapsedTimef() - startTime;
    if (elapsedTime >= timerDuration) {
      isTimerActive = false;
      status = 3;
    }
  }

  // ケーブルの正誤判定
  if (Arduino.available()) {
    int arduinoRead = Arduino.readByte();

    if (arduinoRead) {
      if (arduinoRead == correctCable) {
        status = 1;
      } else {
        status = 2;
      }
      isTimerActive = false;
    }
  }

  std::cout << correctCable << std::endl;
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (!isStarted) {
    title.draw();
  } else if (isTimerActive) {
    // 時間制限の表示
    float elapsedTime = ofGetElapsedTimef() - startTime;
    float remainingTime = timerDuration - elapsedTime;

    int min = static_cast<int>(remainingTime) / 60;
    int sec = static_cast<int>(remainingTime) % 60;
    int msec = static_cast<int>(
        (remainingTime - static_cast<int>(remainingTime)) * 1000 / 10);

    string formattedTime = ofToString(min, 2, '0') + ":" +
                           ofToString(sec, 2, '0') + ":" +
                           ofToString(msec, 2, '0');

    time.update(ofToString(formattedTime));
    time.draw();
  }

  // 画面表示
  if (status == 1) {
    success.draw();
    timerSound.stop();
  } else if (status == 2 || status == 3) {
    failed.draw();
    timerSound.stop();
    failedSound.play();
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
  if (!isStarted) {
    isStarted = true;
    isTimerActive = true;
    startTime = ofGetElapsedTimef();
    timerSound.play();
  }
}

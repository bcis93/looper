#pragma once
#include "Track.h"
#include "Button.h"

class TrackController
{
public:
	TrackController();
	TrackController(Track* track, Button* button);
	~TrackController();
	enum State { idle, recording, playing, waiting, overdub, stopped };
	void tick();
	State getState();
  void stopButton();
  void startButton();
  void resetButton();
private:
	State state;
  State lastState;
	Track* track;
	Button* button;
  bool buttonPressed;
};


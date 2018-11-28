#pragma once
#include "Arduino.h"
#include "TrackController.h"
#include "Button.h"
#include <vector>

class Looper
{
public:
	Looper();
	Looper(Button recPlay);
	~Looper();
//	bool getWaitingToStart();
	void tick();
	void addTrack(TrackController track);
private:
//	bool waitingToStart;
	std::vector<TrackController> trackControllers;
	Button recPlayButton;
	TrackController* masterTrack;
	unsigned trackLength;
	elapsedMillis currentPosition;
	enum State { idle, firstRecording, normalOperation };
	State state;
};


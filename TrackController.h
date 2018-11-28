#pragma once
#include "Track.h"
#include "Button.h"

class TrackController
{
public:
	TrackController();
	TrackController(Track track, Button button);
	~TrackController();
	enum State { idle, recording, playing, waiting, overdub };
	void tick();
	State getState();

private:
	State state;
	Track track;
	Button button;
};


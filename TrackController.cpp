#include "Arduino.h"
#include "TrackController.h"
#include "Globals.h"


TrackController::TrackController()
{
}

TrackController::TrackController(Track track, Button button) {
	this->track = track;
	this->button = button;
	state = idle;
}


TrackController::~TrackController()
{
}

void TrackController::tick()
{
	button.tick();
	bool buttonPressed = button.fell();
	if (buttonPressed) {
		Serial.println("button pressed!");
	}


	//state action
	switch (state)
	{
	case TrackController::idle:
		break;
	case TrackController::recording:
		track.continueRecording();
		break;
	case TrackController::playing:
		track.continuePlaying();
		break;
	case TrackController::waiting:
		break;
	case TrackController::overdub:
		track.continueRecording();
		track.continuePlaying();
		break;
	default:
		break;
	}

	//state update
	switch (state)
	{
	case TrackController::idle:
		if (buttonPressed && (waitingToStart == 0)) {
			//start recording
			waitingToStart++;
			state = recording;
			Serial.println("state: recording");
		}
		else if(buttonPressed && recordingMode && masterDone) {
			//start recording
			state = recording;
			Serial.println("state: recording");
		}
		break;
	case TrackController::recording:
		if (buttonPressed && (waitingToStart == 1)) {
			//stop recording
			//start playing
			waitingToStart++;
			state = playing;
			Serial.println("state: playing");
		}
		else if (masterDone) {
			//stop recording
			//start playing
			state = playing;
			Serial.println("state: playing");
		}
		break;
	case TrackController::playing:
		if (buttonPressed && !recordingMode && masterDone) {
			state = waiting;
			Serial.println("state: waiting");
		}
		if (buttonPressed && recordingMode && masterDone) {
			state = overdub;
			Serial.println("state: overdub");
		}
		break;
	case TrackController::waiting:
		if (buttonPressed && !recordingMode && masterDone) {
			state = playing;
			Serial.println("state: playing");
		}
		if (buttonPressed && recordingMode && masterDone) {
			state = overdub;
			Serial.println("state: overdub");
		}
		break;
	case TrackController::overdub:
		if (masterDone) {
			state = playing;
			Serial.println("state: playing");
		}
		break;
	default:
		break;
	}
}

TrackController::State TrackController::getState()
{
	return state;
}

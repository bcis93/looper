#include "Looper.h"
#include "Globals.h"


Looper::Looper()
{
	state = idle;
	recordingMode = true;
}

Looper::Looper(Button recPlay)
{
	recPlayButton = recPlay;
	state = idle;
	recordingMode = true;
}


Looper::~Looper()
{
}

//bool Looper::getWaitingToStart()
//{
//	return waitingToStart;
//}

void Looper::tick()
{
	for (int i = 0; i < trackControllers.size(); i++) {
		trackControllers[i].tick();
	}

	recPlayButton.tick();
	bool buttonPressed = recPlayButton.fell();

	//state action
	switch (state)
	{
	case Looper::idle:
		currentPosition = 0;
		break;
	case Looper::firstRecording:
		break;
	case Looper::normalOperation:
		if (masterDone) { //masterDone flag should only be true for one tick
			masterDone = false;
		}
		if (currentPosition >= trackLength) {
			masterDone = true;
			currentPosition = 0;
		}
    if (buttonPressed) {
     Serial.println("recPlay button pressed!");
     recordingMode = !recordingMode;
    }
		break;
	default:
		break;
	}

	//state update
	switch (state)
	{
	case Looper::idle:
		for (int i = 0; i < trackControllers.size(); i++) {
			if (trackControllers[i].getState() == TrackController::recording) {
				masterTrack = &trackControllers[i];
				state = firstRecording;
				Serial.println("looper state: firstRecording");
				break;
			}
		}
		break;
	case Looper::firstRecording:
		if (masterTrack->getState() == TrackController::playing) {
			trackLength = currentPosition;
			currentPosition = 0;
			state = normalOperation;
			Serial.println("looper state: normalOperation");
		}
		break;
	case Looper::normalOperation:
		break;
	default:
		break;
	}


//	if (waitingToStart == 0) {
//		currentPosition = 0;
//	}
//	if (waitingToStart == 1) {
//		for (int i = 0; i < trackControllers.size(); i++) {
//			if (trackControllers[i].getState == TrackController::recording) {
//				masterTrack = &trackControllers[i];
//			}
//		}
//	}

	
}

void Looper::addTrack(TrackController track)
{
	trackControllers.push_back(track);
}

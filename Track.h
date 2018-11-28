#pragma once
#include "Button.h"
class Track
{
public:
	Track();
	~Track();
	bool isPlaying();
	bool isRecording();
	void startPlaying();
	void startRecording();
	void stopPlaying();
	void stopRecording();
	void continuePlaying();
	void continueRecording();
private:
	bool playing;
	bool recording;
};


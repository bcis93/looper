#include "Arduino.h"
#include "Track.h"

Track::Track() {
	playing = false;
	recording = false;
}

Track::~Track()
{
}

bool Track::isPlaying() {
	return playing;
}

bool Track::isRecording() {
	return recording;
}

void Track::startPlaying()
{
	Serial.println("startPlaying");
	playing = true;
}

void Track::startRecording()
{
	Serial.println("startRecording");
	recording = true;
}

void Track::stopPlaying()
{
	Serial.println("stopPlaying");
	playing = false;
}

void Track::stopRecording()
{
	Serial.println("stopRecording");
	recording = false;
}

void Track::continuePlaying()
{
}

void Track::continueRecording()
{
}

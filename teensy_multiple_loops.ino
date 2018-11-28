#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce2.h>

#include "Looper.h"
#include "Button.h"
#include "TrackController.h"
#include "Track.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2sInput;           //xy=115,147
AudioPlaySdRaw           playRaw1;       //xy=148.0000228881836,241.00004720687866
AudioMixer4              track1Mixer;    //xy=449.0000534057617,268.00002670288086
AudioMixer4              outputMixer;    //xy=452.0000534057617,154.00000381469727
AudioRecordQueue         queue1;         //xy=608.0000190734863,290.0000114440918
AudioOutputI2S           i2sOutput;      //xy=689.0000190734863,196.0000057220459
AudioConnection          patchCord1(i2sInput, 0, outputMixer, 0);
AudioConnection          patchCord2(i2sInput, 0, track1Mixer, 0);
AudioConnection          patchCord3(playRaw1, 0, outputMixer, 1);
AudioConnection          patchCord4(playRaw1, 0, track1Mixer, 1);
AudioConnection          patchCord5(track1Mixer, queue1);
AudioConnection          patchCord6(outputMixer, 0, i2sOutput, 0);
AudioConnection          patchCord7(outputMixer, 0, i2sOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=256,424


#define REC_PLAY_BUTTON 26
#define TRACK_1_BUTTON 31
#define TRACK_2_BUTTON 32
#define TRACK_3_BUTTON 33
#define TRACK_4_BUTTON 34

bool recordingMode; //true if recording mode, false if playing mode
bool masterDone; //true every time the master track starts over. will stay true only for one tick cycle
int waitingToStart; //0 until the first track starts recording, 1 while the first track is recording, 2 once the first track finishes

//Buttons
Button recPlayButton(REC_PLAY_BUTTON);
Button track1Button(TRACK_1_BUTTON);
Button track2Button(TRACK_2_BUTTON);
Button track3Button(TRACK_3_BUTTON);
Button track4Button(TRACK_4_BUTTON);

//Tracks
Track track1;
Track track2;
Track track3;
Track track4;

//TrackControllers
TrackController track1Controller(track1, track1Button);
TrackController track2Controller(track2, track2Button);
TrackController track3Controller(track3, track3Button);
TrackController track4Controller(track4, track4Button);


Looper looper(recPlayButton);

void setup() {
  looper.addTrack(track1Controller);
  looper.addTrack(track2Controller);
}

void loop() {
  looper.tick();
}

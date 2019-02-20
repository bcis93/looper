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
AudioInputI2S            i2sInput;       //xy=94,96
AudioPlaySdRaw           playRaw1;       //xy=106,179
AudioPlaySdRaw           playRaw2;       //xy=108,239
AudioPlaySdRaw           playRaw3;     //xy=107,300
AudioMixer4              trackMixer;     //xy=428,217
AudioMixer4              outputMixer;    //xy=431,103
AudioRecordQueue         queue1;         //xy=587,239
AudioOutputI2S           i2sOutput;      //xy=668,145
AudioConnection          patchCord1(i2sInput, 0, outputMixer, 0);
AudioConnection          patchCord2(i2sInput, 0, trackMixer, 0);
AudioConnection          patchCord3(playRaw1, 0, outputMixer, 1);
AudioConnection          patchCord4(playRaw1, 0, trackMixer, 1);
AudioConnection          patchCord5(playRaw3, 0, outputMixer, 3);
AudioConnection          patchCord6(playRaw3, 0, trackMixer, 3);
AudioConnection          patchCord7(playRaw2, 0, trackMixer, 2);
AudioConnection          patchCord8(playRaw2, 0, outputMixer, 2);
AudioConnection          patchCord9(trackMixer, queue1);
AudioConnection          patchCord10(outputMixer, 0, i2sOutput, 0);
AudioConnection          patchCord11(outputMixer, 0, i2sOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=144,377
// GUItool: end automatically generated code




#define REC_PLAY_BUTTON     26
#define START_STOP_BUTTON   27
#define TRACK_1_BUTTON      31
#define TRACK_2_BUTTON      32
#define TRACK_3_BUTTON      33
#define TRACK_4_BUTTON      34

#define SDCARD_CS_PIN       BUILTIN_SDCARD
#define SDCARD_MOSI_PIN     11  // not actually used
#define SDCARD_SCK_PIN      13  // not actually used

// which input on the audio shield will be used?
const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

bool recordingMode; //true if recording mode, false if playing mode
bool masterDone; //true every time the master track starts over. will stay true only for one tick cycle
int waitingToStart; //0 until the first track starts recording, 1 while the first track is recording, 2 once the first track finishes

//Buttons
Button recPlayButton(REC_PLAY_BUTTON);
Button startStopButton(START_STOP_BUTTON);
Button track1Button(TRACK_1_BUTTON);
Button track2Button(TRACK_2_BUTTON);
Button track3Button(TRACK_3_BUTTON);
Button track4Button(TRACK_4_BUTTON);

//Tracks
Track track1(1, &queue1, &playRaw1, &trackMixer);
Track track2(2, &queue1, &playRaw2, &trackMixer);
Track track3(3, &queue1, &playRaw3, &trackMixer);
//Track track4(4, &queue1, &playRaw1);

//TrackControllers
TrackController track1Controller(&track1, &track1Button);
TrackController track2Controller(&track2, &track2Button);
TrackController track3Controller(&track3, &track3Button);
//TrackController track4Controller(&track4, &track4Button);


Looper looper(&recPlayButton, &startStopButton);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup...");

  // Audio connections require memory, and the record queue
  // uses this memory to buffer incoming audio.
  AudioMemory(160);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(.8);

  // Initialize the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here if no SD card, but print a message
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  if (SD.exists("TEST.RAW")) {
    SD.remove("TEST.RAW");
  }
  File file = SD.open("TEST.RAW", FILE_WRITE);
  if (!file){
    while (1) {
      Serial.println("Failed to open...");
      delay(500);
    }
  }


  outputMixer.gain(0, .8);
  outputMixer.gain(1, .8);
  outputMixer.gain(2, .8);
  outputMixer.gain(3, .8);
  
  
  looper.addTrack(&track1Controller);
  looper.addTrack(&track2Controller);
  looper.addTrack(&track3Controller);
  Serial.println("Setup complete!");
}

void loop() {
  looper.tick();
}

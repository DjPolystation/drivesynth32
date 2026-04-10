// Drivesynth ESP32-based HDD sound emulator using the XTronical DAC Audio Library
// Requires XTronical DAC Audio Library 4.2.1

#include "SoundData.h"
#include "XT_DAC_Audio.h"

XT_Wav_Class Idle(Idlesnd);
XT_Wav_Class Boot(Bootsnd);
XT_Wav_Class HeadTick(HeadTickSnd);
XT_DAC_Audio_Class DacAudio(25,0);
uint32_t DemoCounter=0;
const int signalPin = 13;
int state = 0;
unsigned long startTime = 0;
bool pulsing = false;


void setup() {
  pinMode(signalPin, INPUT);
  DacAudio.FillBuffer(); 
  Serial.begin(115200);
  delay (1000);
  DacAudio.Play(&Boot);  // Disc starts spinning 
  
}

void loop() {

  int pinstate = digitalRead(signalPin);

  DacAudio.FillBuffer(); // Fill the sound buffer with data
  if (state == 0) {
    // waiting for the disc starting sound to finish
    if (!Boot.Playing) {
      state = 1;
       }
     }

if (state == 1 && Idle.Playing==false){  // Playing the disc spinning noise loop
      DacAudio.Play(&Idle);
      delay(80);  // Added delay to loop correctly (don't know why but without this delay it loops badly)
    }
   

if (pinstate == HIGH && !pulsing) {
    // Reading Pulse Start from HDD Led header
    pulsing = true;
    startTime = millis();
  }

 if (pinstate == LOW && pulsing) {
    // Reading Pulse Stop from HDD Led header
    unsigned long sigpulse = millis() - startTime;
    pulsing = false;

    Serial.println(sigpulse);

    if ((sigpulse <= 100) && (HeadTick.Playing == false) && ((rand() % 2) + 1 ==  2)) {  // playing hdd activity sound when pulses comes out from the HDD LED pin header. I added a 50/50 randomicity to simulate file fragmentation
      DacAudio.Play(&HeadTick);
    }
  }  
}

# A fake noisy HDD for your silent vintage computer

I just finished restoring an IBM PS/2 modle 30.
Replaced the original HDD with a CF-Card and when i turned it on i felt like... it was missing something

So i just grabbed an ESP32 and put on a bunch of lines of code to simulate an HDD sound

The project goal is to make it as cheaper and easier as possible with minimal additional components

# Files Overview
It's fairly simple.
There are two files.

Drivesynth.ino   Contains the actual code

Sounddata.h      Contains Raw audio data sampled from my IBM Model 30 HDD

# ESP32 Setup
You'll need to install the XTronical Audio DAC Library 

- download it from [here](https://www.xtronical.com/wp-content/uploads/2019/10/XT_DAC_Audio-4_2_1.zip)
- in arduino IDE go to Sketch > Include Library > Add from Zip and then select the zip file you just downloaded
- Now open the drivesynth.ino file and you should be able to compile and upload to your ESP32

# Wire Setup
Pin VIN    ---->   5V source from PC (it can be from a PS/2 connector or from the red wire of a molex)

Pin GND    ---->   PC-GND and Negative Speaker

Pin D25    ---->   Audio Output (positive speaker)

Pin D13    ---->   PC HDD Led positive Pin from Pin header on motherboard (you will need a voltage divider or a level shifter because it's a 5VPP digital signal and the ESP works only with 3.3V signals)

# Todo
  - Make it more polished
    For now it is just a bunch of wire on a breadboard
  
  - Provide an easier method to upload samples from different HDDs
    At this moment, sound samples are hardcoded as raw data into the sounddata.h file

  - Maybe making a PCB
    Still unsure if i want to make an ISA card or an HDD-Caddy card with molex and various cables

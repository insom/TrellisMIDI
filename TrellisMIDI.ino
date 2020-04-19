#include <Adafruit_NeoTrellisM4.h>

#define MIDI_CHANNEL 0

Adafruit_NeoTrellisM4 trellis = Adafruit_NeoTrellisM4();

int semitones[16] = {
    -1, 1, 3, -1, 6, 8, 10, -2,
    0,  2, 4,  5, 7, 9, 11, -3,
};

byte octaveBaseNotes[] = {
    24, 36, 48, 60, 72, 84, 96, 108,
};

int topOctave = 1, bottomOctave = 3; // Just pleasant defaults

void offColor(int key, int octave) {
  if (semitones[key % 16] < 0) {
    trellis.setPixelColor(key, 0);
  } else {
    trellis.setPixelColor(key, Wheel(octaveBaseNotes[octave]));
  }
}

void setup() {
  trellis.begin();
  trellis.setBrightness(80);
  trellis.enableUSBMIDI(true);
  trellis.enableUARTMIDI(true);
  trellis.setUSBMIDIchannel(MIDI_CHANNEL);
  trellis.setUARTMIDIchannel(MIDI_CHANNEL);
  for (byte i = 0; i < 32; i++)
    offColor(i, i < 16 ? topOctave : bottomOctave);
}

void loop() {
  trellis.tick();

  while (trellis.available()) {
    keypadEvent e = trellis.read();
    int key = e.bit.KEY;
    int octave;

    if (key > 15) {
      octave = bottomOctave;
    } else {
      octave = topOctave;
    }
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      trellis.setPixelColor(key, Wheel(random(255)));
    } else if (e.bit.EVENT == KEY_JUST_RELEASED) {
      offColor(key, octave);
    }

    if (semitones[key % 16] >= 0) {
      if (e.bit.EVENT == KEY_JUST_PRESSED) {
        trellis.noteOn(semitones[key % 16] + octaveBaseNotes[octave], 64);
      } else if (e.bit.EVENT == KEY_JUST_RELEASED) {
        trellis.noteOff(semitones[key % 16] + octaveBaseNotes[octave], 64);
      }
    } else {
      // metakeys!
      if (e.bit.EVENT == KEY_JUST_PRESSED) {
        if (key == 7)
          topOctave++;
        if (key == 15)
          topOctave--;
        if (key == 23)
          bottomOctave++;
        if (key == 31)
          bottomOctave--;
        // Limiting. I'm sure I could be more clever than this ...
        if (topOctave > 7)
          topOctave = 7;
        if (bottomOctave > 7)
          bottomOctave = 7;
        if (topOctave < 0)
          topOctave = 0;
        if (bottomOctave < 0)
          bottomOctave = 0;
        for (int i = 0; i < 32; i++)
          offColor(i, i < 16 ? topOctave : bottomOctave);
      }
    }
  }
  trellis.sendMIDI();
  delay(10);
}

/* vvv Adafruit Example Code vvv */

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return trellis.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return trellis.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return trellis.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

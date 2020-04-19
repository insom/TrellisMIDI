## TrellisMIDI

This turns your [NeoTrellis](https://www.adafruit.com/product/4020) into a two octave MIDI controller with switchable octaves.

The "how do I MIDI stuff" is straight from [John Park's guide](https://learn.adafruit.com/trellis-m4-midi-keypad-and-tilt-controller) but I found this useful enough to share with others.

### Requirements

Requires Arduino IDE 1.8 or greater.

Use the Adafruit Trellis M4 board type, from [the Adafruit board index](https://adafruit.github.io/arduino-board-index/package_adafruit_index.json)

(If you don't know what this means, [follow Adafruit's setup guide for this board](https://learn.adafruit.com/adafruit-neotrellis-m4/setup))

Install the following libraries from the library manager:

* `Adafruit_Keypad`
* `Adafruit_NeoPixel`
* `Adafruit_NeoPixel_ZeroDMA`
* `MIDIUSB`

Then compile and upload.

### How do I use it?

The right-most column selects octaves for the top and bottom "keybed" -- up for higher octaves, down for lower octaves. The colour of the keybed moves from red (for very bassy) through green to blue (for very high-pitched).

It will show up as a MIDI device if plugged into an iPad or computer, and will also output MIDI over the "STEMMA" connector at the top of the board. [Back to Adafruit to learn how to build the cable you'll need](https://learn.adafruit.com/classic-midi-synth-control-with-trellis-m4)

The notes are laid out on the grid the same as the full twelve-equal-tone layout used by the Novation Circuit.

Have fun!

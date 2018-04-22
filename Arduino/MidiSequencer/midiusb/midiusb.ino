#include "MIDIUSB.h"

const int MIDI_CHANNEL = 1;
const int NUM_ROWS = 4;
const int NUM_COLS = 4;
const int NUM_PINS = NUM_ROWS * NUM_COLS;

const byte buttons[NUM_ROWS][NUM_COLS] = {{2, 3, 4, 5}};
                                    {6, 7, 8, 9},
                                    {10, 11, 12, 13},
                                    {A0, A1, A2, A3}};
int bVals[NUM_ROWS][NUM_COLS];
int lastBVals[NUM_ROWS][NUM_COLS];

void setup() {
  // Set pinMode for all buttons
  for (int i=0; i < NUM_ROWS; i++)
    for (int j=0; j < NUM_COLS; j++)
    {
      pinMode(buttons[i][j], INPUT_PULLUP);
      bVals[i][j] = 0;
      lastBVals[i][j] = 0;
    }
}

void loop() {

  for (int i=0; i < NUM_ROWS; i++)
  {
    for (int j=0; j < NUM_COLS; j++)
    {
      bVals[i][j] = digitalRead(buttons[i][j]);
      if (bVals[i][j] != lastBVals[i][j])
      {
        int noteNumber = button_index_to_midi_num(i,j);
        lastBVals[i][j] = bVals[i][j];
        if (bVals[i][j] == HIGH)
        {
            noteOn(MIDI_CHANNEL, noteNumber, 127);
            MidiUSB.flush();
        }
        else
        {
            noteOff(MIDI_CHANNEL, noteNumber, 0);
            MidiUSB.flush();
        }
      }
    }
  }
}

int button_index_to_midi_num(int r, int c)
{
  return 16 * r + c;
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

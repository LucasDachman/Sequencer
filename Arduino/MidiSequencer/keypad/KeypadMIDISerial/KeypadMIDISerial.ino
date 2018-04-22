
#include <Keypad.h>
#include "MIDIUSB.h"

const int MIDI_CHANNEL = 1;
const byte ROWS = 4;
const byte COLS = 4;
const byte N_KEYS = ROWS * COLS;
char keys[ROWS][COLS] = {
{'a','b','c','d'},
{'e','f','g','h'},
{'i','j','k','l'},
{'m','n','o','p'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;

int output[ROWS][COLS] = {
                          {0, 0, 0, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0},
                          {0, 0, 0, 0}
                        };


void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
    Serial.print("LIST_MAX");
    Serial.println(LIST_MAX);
}


void loop() {
    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<N_KEYS; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                int r = kpd.key[i].kcode / ROWS;
                int c = kpd.key[i].kcode % COLS;
                int noteNumber = button_index_to_midi_num(r,c);
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                  case PRESSED:
                    output[r][c] = 1;
                    printOutput();
                    noteOn(MIDI_CHANNEL, noteNumber, 127);
                    MidiUSB.flush();
                break;
                  case RELEASED:
                    output[r][c] = 0;
                    printOutput();
                    noteOff(MIDI_CHANNEL, noteNumber, 0);
                    MidiUSB.flush();
                break;
                }
            }
        }
    }
}  // End loop

void printOutput()
{
  for (int i=0; i<ROWS; i++)
  {
    for (int j=0; j<COLS; j++)
    {
      Serial.print(output[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println("==========");
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

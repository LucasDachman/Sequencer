#include <MIDI.h>

const int MIDI_BAUD_RATE = 31250;
const int MIDI_CHANNEL = 1;
const int NUM_ROWS = 4;
const int NUM_COLS = 4;
const int NUM_PINS = NUM_ROWS * NUM_COLS;

const byte buttons[4][4] = {{2, 3, 4, 5},
                              {6, 7, 8, 9},
                              {10, 11, 12, 13},
                              {A0, A1, A2, A3}};

int bVals[4][4] = {{0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};

int lastBVals[4][4] = {{0, 0, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  // Set pinMode for all buttons
  for (int i=0; i < NUM_ROWS; i++)
    for (int j=0; j < NUM_COLS; j++) {
      pinMode(buttons[i][j], INPUT_PULLUP);
      //digitalWrite(buttons[i][j], HIGH);
    }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
}

void loop()
{
  for (int i=0; i < NUM_ROWS; i++)
  {
    for (int j=0; j < NUM_COLS; j++)
    {

      bVals[i][j] = digitalRead(buttons[i][j]);
      if (bVals[i][j] != lastBVals[i][j])
      {
        int noteNumber = button_index_to_midi_num(i,j);
        lastBVals[i][j] = bVals[i][j];
        if (bVals[i][j] == LOW)
        {
            MIDI.sendNoteOn(noteNumber, 127, MIDI_CHANNEL);
        }
        else
        {
            MIDI.sendNoteOff(noteNumber, 0 , MIDI_CHANNEL);
        }
      }
    }
  }
}

int button_index_to_midi_num(int r, int c)
{
  return 16 * r + c;
}

#include <MIDI.h>

const int MIDI_SERIAL_BAUD_RATE = 11520;
const int MIDI_CHANNEL = 1;
const int NUM_ROWS = 4;
const int NUM_COLS = 4;
const int NUM_PINS = NUM_ROWS * NUM_COLS;

int readXY(int x, int y);
int button_index_to_midi_num(int r, int c);

MIDI_CREATE_DEFAULT_INSTANCE();

const int rowPins[] = {6, 7, 8, 9};
const int colPins[] = {10, 11, 12, 13};
int val[][NUM_COLS] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

int lastval [][NUM_COLS]=  {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(MIDI_SERIAL_BAUD_RATE);
//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      val[i][j] = readXY(i, j);
      if (val[i][j] != lastval[i][j])
      {
        int noteNumber = button_index_to_midi_num(i,j);
        lastval[i][j] = val[i][j];
        if (val[i][j] == LOW)
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
  delay(100);
}

int readXY(int x, int y) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(colPins[i], HIGH);
  }
  digitalWrite(colPins[y], LOW);
  int tempVal = digitalRead(rowPins[x]);
  return tempVal;
}

int button_index_to_midi_num(int r, int c)
{
  return 16 * r + c;
}

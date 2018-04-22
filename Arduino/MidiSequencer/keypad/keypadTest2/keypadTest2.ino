
#include <Keypad.h>

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
byte colPins[COLS] = {10,11,12,13}; //connect to the column pinouts of the kpd

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
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                  case PRESSED:
                    output[r][c] = 1;
                    printOutput();
                break;
                  case RELEASED:
                    output[r][c] = 0;
                    printOutput();
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
}

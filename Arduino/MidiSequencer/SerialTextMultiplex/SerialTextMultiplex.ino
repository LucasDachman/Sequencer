

const int NUM_ROWS = 4;
const int NUM_COLS = 4;

int compareArrays(int [][NUM_COLS], int [][NUM_COLS]);
int readXY(int x, int y);
void clearMatrix(int m[][NUM_COLS]);

const int rowPins[] = {6, 7, 8, 9};
const int colPins[] = {10, 11, 12, 13};

int val[][NUM_COLS] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

int lastVal [][NUM_COLS]=  {
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
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      val[i][j] = readXY(i, j);
    }
  }
  // print matrix if changed
  if (!compareArrays(val, lastVal))
  {
    for (int i = 0; i < NUM_ROWS; i++) {
      for (int j = 0; j < NUM_COLS; j++) {
        lastVal[i][j] = val[i][j];
        Serial.print(val[i][j]);
        Serial.print(" ");
      }
      Serial.println();
    }
    Serial.println("================");
  }
  Serial.println();
  delay(180);
}

int readXY(int x, int y) {
  int ret = 0;
  for (int i = 0; i < 4; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  digitalWrite(colPins[y], LOW);
  pinMode(rowPins[x], INPUT_PULLUP);
  ret |= digitalRead(rowPins[x]);

  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  digitalWrite(rowPins[x], LOW);
  pinMode(colPins[y], INPUT_PULLUP);
  ret |= digitalRead(colPins[y]);

  return ret;
}

int compareArrays(int a [][NUM_COLS], int b [][NUM_COLS])
{
  for (int i = 0; i < NUM_ROWS; i++)
      for (int j = 0; j < NUM_COLS; j++)
        if (a[i][j] != b[i][j])
          return false;
  return true;
}

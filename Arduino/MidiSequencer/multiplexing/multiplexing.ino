const int rowPins[] = {6, 7, 8, 9};
const int colPins[] = {2,3,4,5};
int val[][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};
int skip = 0;

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
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      val[i][j] = readXY(i, j);
      Serial.print(val[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
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

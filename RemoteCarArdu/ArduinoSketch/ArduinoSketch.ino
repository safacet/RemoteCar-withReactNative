
const int engineA1 = 8; // IN = 1 right
const int engineA2 = 6; // IN = 2 right
const int enA = 10 ; // Enable A


const int engineB1 = 5; //IN = 3 left
const int engineB2 = 7; // IN = 4 left
const int enB = 9; // EnableB

char HelloMobile;  //For the message mobile phone sent after connection
String measures;  //message comes from mobile phone
String x; // after parsing x value string
String y; // after parsing y value string



int i;
int j;

float xVal;  //final x value
float yVal;  //final y value
int engspeed; // calculated motor speed from yVal value
int Aspeed;   // Right motors final speed
int Bspeed;   // Left motors final speed
bool checkspeed;

void setup() {
  Serial.begin(115200);
  pinMode(engineA1, OUTPUT);
  pinMode(engineA2, OUTPUT);
  pinMode(engineB1, OUTPUT);
  pinMode(engineB2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  while (true) {
    if (Serial.available() > 0) {
      HelloMobile = Serial.read();
      if (HelloMobile == '!') {
        break;
      }
    }
  }

}

void loop() {

  if (Serial.available() > 0) {

    measures = Serial.readStringUntil('!');
    x = "";
    y = "";

    for (i = 0; measures[i] != '/'; i++) {
      y += measures[i];
      if (i > 4) {
        break;
      }
    }
    for (j = i + 1; measures[j] != '?'; j++) {
      x += measures[j];
      if (j > 10) {
        break;
      }
    }
    yVal = y.toFloat();
    xVal = x.toFloat();
    if (xVal > 0.5) {
      xVal = 0.5;
    }
    else if (xVal < -0.5) {
      xVal = -0.5;
    }
    if (yVal > 0.5) {
      yVal = 0.5;
    }
    else if (yVal < -0.5) {
      yVal = -0.5;
    }
  }
  if (yVal > 0.1) { //Forward
    digitalWrite(engineA1, HIGH);
    digitalWrite(engineA2, LOW);
    digitalWrite(engineB1, HIGH);
    digitalWrite(engineB2, LOW);

    checkspeed = true;
    engspeed = map(yVal, 0.1, 0.5, 100, 255);
  } else if (yVal < -0.1) { //Backward
    digitalWrite(engineA1, LOW);
    digitalWrite(engineA2, HIGH);
    digitalWrite(engineB1, LOW);
    digitalWrite(engineB2, HIGH);

    checkspeed = true;
    engspeed = map(yVal, -0.1, -0.5, 100, 255);
  } else { //there is no y direction speed
    checkspeed = false;
    if (abs(xVal) < 0.1) { // there is no x direction speed
      digitalWrite(engineA1, LOW);
      digitalWrite(engineA2, LOW);
      digitalWrite(engineB1, LOW);
      digitalWrite(engineB2, LOW);
    } else if (xVal > 0.1) { // only turning right
      digitalWrite(engineA1, LOW);
      digitalWrite(engineA2, HIGH);
      digitalWrite(engineB1, HIGH);
      digitalWrite(engineB2, LOW);
      } else {                // only turning left
      digitalWrite(engineA1, HIGH);
      digitalWrite(engineA2, LOW);
      digitalWrite(engineB1, LOW);
      digitalWrite(engineB2, HIGH);
      }
    }
    if (checkspeed) {
    Aspeed = engspeed - map(xVal, -0.5, 0.5, -255, 255);
    Bspeed = engspeed + map(xVal, -0.5, 0.5, -255, 255);
    } else {
      Aspeed = map(abs(xVal), 0.1, 0.5, 100, 255);
      Bspeed = Aspeed;
    }
    if (Aspeed < 100) Aspeed = 100;
    if (Aspeed > 255) Aspeed = 255;
    if (Bspeed < 100) Bspeed = 100;
    if (Bspeed > 255) Bspeed = 255;
  }

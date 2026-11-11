/*
  Magnetic Mystery Puzzle
 Juniper Tech Labs

  Move a magnet over 4 sensors in the right order to solve the puzzle.
  A new random pattern is made each time you win.

  Wiring:
    Sensors 0–3 -> pins 2, 3, 4, 5 (other leg to GND, uses INPUT_PULLUP)
    Green LED   -> pin 6 (through a 220Ω resistor)
    Red LED     -> pin 7 (through a 220Ω resistor)
    A0          -> leave unconnected (used for random seed)

  Board: Arduino Uno / Nano
*/

int sensorPin0 = 2;
int sensorPin1 = 3;
int sensorPin2 = 4;
int sensorPin3 = 5;

int greenLed = 6;
int redLed = 7;

// One of each sensor number. The code shuffles these into a random order.
int secretPattern[4] = { 0, 1, 2, 3 };

int currentStep = 0;

int playerInput[4] = { -1, -1, -1, -1 };

bool wasActive0 = false;
bool wasActive1 = false;
bool wasActive2 = false;
bool wasActive3 = false;


void setup() {
  Serial.begin(9600);

  pinMode(sensorPin0, INPUT_PULLUP);
  pinMode(sensorPin1, INPUT_PULLUP);
  pinMode(sensorPin2, INPUT_PULLUP);
  pinMode(sensorPin3, INPUT_PULLUP);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  // Read the noise on an empty analog pin to get a different random pattern each time
  randomSeed(analogRead(A0));

  delay(1000);
  Serial.println("Magnetic_Mystery_Puzzle_4");
  Serial.println("Move the magnet over the sensors to try to guess the pattern");
  generatePattern();

  for (int i = 3; i > 0; i--) {
    digitalWrite(greenLed, HIGH);
    delay(150);
    digitalWrite(greenLed, LOW);
    delay(150);
    digitalWrite(redLed, HIGH);
    delay(150);
    digitalWrite(redLed, LOW);
    delay(150);
  }
}

void loop() {

  bool sensor0 = (digitalRead(sensorPin0) == LOW);
  bool sensor1 = (digitalRead(sensorPin1) == LOW);
  bool sensor2 = (digitalRead(sensorPin2) == LOW);
  bool sensor3 = (digitalRead(sensorPin3) == LOW);

  if (sensor0 && !wasActive0) {
    digitalWrite(greenLed, HIGH);
    delay(250);
    digitalWrite(greenLed, LOW);
    Serial.println("Sensor 0 detected");
    wasActive0 = true;
    recordSensor(0);
  }
  if (!sensor0) wasActive0 = false;

  if (sensor1 && !wasActive1) {
    digitalWrite(greenLed, HIGH);
    delay(250);
    digitalWrite(greenLed, LOW);
    Serial.println("Sensor 1 detected");
    wasActive1 = true;
    recordSensor(1);
  }
  if (!sensor1) wasActive1 = false;

  if (sensor2 && !wasActive2) {
    digitalWrite(greenLed, HIGH);
    delay(250);
    digitalWrite(greenLed, LOW);
    Serial.println("Sensor 2 detected");
    wasActive2 = true;
    recordSensor(2);
  }
  if (!sensor2) wasActive2 = false;

  if (sensor3 && !wasActive3) {
    digitalWrite(greenLed, HIGH);
    delay(250);
    digitalWrite(greenLed, LOW);
    Serial.println("Sensor 3 detected");
    wasActive3 = true;
    recordSensor(3);
  }
  if (!sensor3) wasActive3 = false;
}

void recordSensor(int sensorNumber) {
  playerInput[currentStep] = sensorNumber;
  currentStep++;

  if (currentStep == 4) {
    checkPattern();
  }
}

void checkPattern() {

  bool correct = true;

  for (int i = 0; i < 4; i++) {
    if (playerInput[i] != secretPattern[i]) {
      correct = false;
      break;
    }
  }

  delay(1000);

  if (correct) {
    Serial.println("You win! Pattern CORRECT!");
    for (int i = 0; i < 5; i++) {
      digitalWrite(greenLed, HIGH);
      delay(300);
      digitalWrite(greenLed, LOW);
      delay(300);
    }
    // They got it right, so make a new secret pattern
    generatePattern();
  } else {
    Serial.println("You lose! Pattern INCORRECT");
    for (int i = 0; i < 5; i++) {
      digitalWrite(redLed, HIGH);
      delay(300);
      digitalWrite(redLed, LOW);
      delay(300);
    }
    // They got it wrong, so keep the same secret pattern and let them try again
  }

  resetPuzzle();
}


void resetPuzzle() {

  currentStep = 0;
  playerInput[0] = -1;
  playerInput[1] = -1;
  playerInput[2] = -1;
  playerInput[3] = -1;
}

// Shuffles secretPattern into a new random order and prints it
void generatePattern() {

  // Swap each spot with a random spot from here to the end.
  // Only the order changes, so each sensor is still used exactly once.
  for (int i = 0; i < 4; i++) {
    int j = random(i, 4);
    int temp = secretPattern[i];
    secretPattern[i] = secretPattern[j];
    secretPattern[j] = temp;
  }

  Serial.print("Winning pattern: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(secretPattern[i]);
    if (i < 3) {
      Serial.print(", ");
    }
  }
  Serial.print("\n");
}

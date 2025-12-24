#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8,9,4,5,6,7);

// L298N motor driver pins
const int ENA = 3;   // Enable pin for left motor (PWM)
const int IN1 = 2;   // Left motor direction 1
const int IN2 = 1;   // Left motor direction 2
const int ENB = 11;  // Enable pin for right motor (PWM)
const int IN3 = 12;  // Right motor direction 1
const int IN4 = 13;  // Right motor direction 2

#define leftIR A1
#define rightIR A2

unsigned long previousTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Robot Car Ready");
  delay(2000);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  previousTime = millis(); // record start time
}

void loop() {
  unsigned long currentTime = (millis() - previousTime) / 1000; // seconds

  lcd.setCursor(0, 0);
  lcd.print("Moving forward  ");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(currentTime);
  lcd.print(" sec ");

  bool L = digitalRead(leftIR); 
  bool R = digitalRead(rightIR);

  if (L && R) {
    moveForward();
  }
  else if (!L && R) {
    while (!digitalRead(leftIR) && digitalRead(rightIR)) {
      turnLeft();
      delay(55);                 
    }
  }
  else if (L && !R) {
    while (!digitalRead(rightIR) && digitalRead(leftIR)) {
      turnRight();
      delay(55);              
    }
  }
  else {
    stop();
    while (true);
  }
}

// Move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 120);
  analogWrite(ENB, 120);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  delay(100);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
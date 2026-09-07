#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHT_IN 24
#define DHT_OUT 25

LiquidCrystal LCD(3, 5, 9, 10, 11, 12);

DHT dhtIn(DHT_IN, DHTTYPE);
DHT dhtOut(DHT_OUT, DHTTYPE);

const byte trigPin = 2;
const byte echoPin = 4;
const byte buzzerPin = 13;

const byte solarA = A0;
const byte solarB = A1;
const byte windPin = A2;

void setup() {
  LCD.begin(16, 2);

  dhtIn.begin();
  dhtOut.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  ShowTemperature();
  WaitAndCheck(5000);

  ShowSolar();
  WaitAndCheck(5000);

  ShowWind();
  WaitAndCheck(5000);
}

float Distance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void CheckBuzzer() {

  float d = Distance();

  if (d < 7) {
    tone(buzzerPin, 1000);
  }
  else if (d < 20) {
    tone(buzzerPin, 1000);
    delay(100);
    noTone(buzzerPin);
  }
  else {
    noTone(buzzerPin);
  }
}

void WaitAndCheck(unsigned long ms) {

  for (unsigned long t = 0; t < ms; t += 100) {
    CheckBuzzer();
    delay(100);
  }
}

void ShowTemperature() {

  float in = dhtIn.readTemperature();
  float out = dhtOut.readTemperature();

  LCD.clear();

  LCD.setCursor(0, 0);
  LCD.print("In : ");
  LCD.print(in, 1);
  LCD.print((char)223);
  LCD.print("C");

  LCD.setCursor(0, 1);
  LCD.print("Out: ");
  LCD.print(out, 1);
  LCD.print((char)223);
  LCD.print("C");
}

void ShowSolar() {

  LCD.clear();

  LCD.setCursor(0, 0);
  LCD.print("SolarA:");
  LCD.print(analogRead(solarA));

  LCD.setCursor(0, 1);
  LCD.print("SolarB:");
  LCD.print(analogRead(solarB));
}

void ShowWind() {

  LCD.clear();

  LCD.setCursor(0, 0);
  LCD.print("Wind Power");

  LCD.setCursor(0, 1);
  LCD.print(analogRead(windPin));
}

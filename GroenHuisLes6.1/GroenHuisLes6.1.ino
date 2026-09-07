#include <LiquidCrystal.h>
#include <DHT.h>

// ---------------- LCD ----------------
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(3, 5, 9, 10, 11, 12);

// ---------------- DHT ----------------
#define DHTTYPE DHT11
#define DHTPIN1 24
#define DHTPIN2 A0

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// ---------------- ANALOGE SENSOREN ----------------
#define LDRPIN    A3
#define SOLAR1PIN A4
#define SOLAR2PIN A5
#define MOTORPIN  A6

// ---------------- OUTPUTS ----------------
#define LED1 6
#define LED2 8
#define BUZZER 13

// ---------------- HC-SR04 ----------------
#define TRIGPIN 2
#define ECHOPIN 4

void setup() {
  lcd.begin(16, 2);

  dht1.begin();
  dht2.begin();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MOTORPIN, INPUT);

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  lcd.clear();
  // display Temperatures for 5 seconds
  // after that display Solar power for 5 seconds
  // and lastly display Wind power for 5 seconds
  for (uint16_t i = 0; i < 300; i++) {
    if (i == 0) DisplayTemperature();
    else if (i >= 100 && i < 200) {
      lcd.clear();
      DisplaySolarPower();
    }
    else {
      lcd.clear();
      DisplayWindPower();
    }

    if (ReadUltrasonicSensor() < 20) {
      // turn on buzzer
      delay(5);
      // turn off buzzer
      delay(45);
    }
    else delay(50);
  }
}

float ReadUltrasonicSensor() {
  float distance = 0;
  // read UltrasonicSensor, and store value
  // in the "distance" variable within this function

  return distance;
}

void DisplayTemperature() {
  // read inside & outside temperature from
  // the DHT11's
  //  ReadDHT11();
  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();

  // display the inside & outside temperature
  // on the LCD
  /* Example:
     Temp In: 23.5c
     Temp Out: 22.8c
  */
  lcd.setCursor(0, 0);
  lcd.print("Temp1:");
  lcd.print(isnan(t1) ? 0 : t1, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Temp2:");
  lcd.print(isnan(t2) ? 0 : t2, 1);
  lcd.print("C");

}

void DisplaySolarPower() {
  // read the power output of both solar panels

  // display both values on the LCD
  /* Example:
     Solar A: 238
     Solar B: 140
  */
  int solar1 = analogRead(SOLAR1PIN);
  int solar2 = analogRead(SOLAR2PIN);

  lcd.setCursor(0, 0);
  lcd.print("Solar1:");
  lcd.print(solar1);

  lcd.setCursor(0, 1);
  lcd.print("Solar2:");
  lcd.print(solar2);

}

void DisplayWindPower() {
  // read the power output of the windmill

  // display wind power on the LCD
  /* Example:
     Windmill: 238
  */

  int motor  = analogRead(MOTORPIN);
  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.print(motor);

}

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

// ---------------- VARIABLES ----------------
long duration;
float distance;

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

  // ---------------- SENSOREN ----------------
  float t1 = dht1.readTemperature();
  float t2 = dht2.readTemperature();

  int ldr    = analogRead(LDRPIN);
  int solar1 = analogRead(SOLAR1PIN);
  int solar2 = analogRead(SOLAR2PIN);
  int motor  = analogRead(MOTORPIN);

  // ---------------- LEDS ----------------
  digitalWrite(LED1, ldr < 500);
  digitalWrite(LED2, ldr < 500);

  // ---------------- MOTOR LOGICA ----------------
  if (solar1 > 300 || solar2 > 300) {
    digitalWrite(MOTORPIN, HIGH);
  } else {
    digitalWrite(MOTORPIN, LOW);
  }

  // ---------------- BUZZER LOGICA ----------------
  if (distance < 3) {

    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, LOW);
    delay(50);
  }
  else if (distance < 15) {

    digitalWrite(BUZZER, HIGH);
    delay(10);
    digitalWrite(BUZZER, LOW);
    delay(90);
  }
  else {
    digitalWrite(BUZZER, LOW);
  }

  // ---------------- SERIAL MONITOR ----------------
  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ---------------- LCD PAGINA 1 ----------------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T1:");
  lcd.print(isnan(t1) ? 0 : t1, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("T2:");
  lcd.print(isnan(t2) ? 0 : t2, 1);
  lcd.print("C");

  delay(3000);

  // ---------------- LCD PAGINA 2 ----------------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.print(motor);

  delay(3000);

  // ---------------- LCD PAGINA 3 ----------------
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(solar1);

  lcd.setCursor(0, 1);
  lcd.print("S2:");
  lcd.print(solar2);

  delay(3000);
}

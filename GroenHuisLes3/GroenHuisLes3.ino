#include <LiquidCrystal.h>
#include <DHT.h>

// ===== LCD =====
LiquidCrystal lcd(3, 5, 9, 10, 11, 12);

// ===== DHT11 =====
#define DHTTYPE DHT11
uint8_t DHTPin = 24;
DHT dht(DHTPin, DHTTYPE);

// ===== HC-SR04 =====
const int trigPin = 2;
const int echoPin = 4;

// ===== Buzzer =====
const int buzzerPin = 13;

long duration;
float distance;

float Temperature, Humidity, HeatIndex;

void setup() {
  Serial.begin(9600);

  dht.begin();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Systeem Start");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  delay(2000);
  lcd.clear();
}

void loop() {

  // DHT11 uitlezen
  ReadDHT11();

  // HC-SR04 triggeren
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // Afstand berekenen
  distance = duration * 0.034 / 2;

  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ===== LCD WEERGAVE =====
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(Temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Afst:");
  lcd.print(distance, 0);
  lcd.print("cm    ");

  // ===== Buzzer =====
  if (distance < 7) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }
  else if (distance < 20) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(900);
  }
  else {
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }

  delay(1000);
}

void ReadDHT11() {

  float temperature =
      round(dht.readTemperature() * 10) / 10;

  float humidity =
      round(dht.readHumidity() * 10) / 10;

  float heatIndex =
      round(dht.computeHeatIndex(
      temperature,
      humidity,
      false) * 10) / 10;

  if (isnan(temperature) ||
      isnan(humidity) ||
      isnan(heatIndex)) {

    Serial.println("DHT11 sensor error");
  }
  else {

    Temperature = temperature;
    Humidity = humidity;
    HeatIndex = heatIndex;

    Serial.println("----- DHT11 -----");
    Serial.println("Temp: " + String(Temperature) + " C");
    Serial.println("Humidity: " + String(Humidity) + " %");
    Serial.println("Heat Index: " + String(HeatIndex) + " C");
    Serial.println();
  }
}

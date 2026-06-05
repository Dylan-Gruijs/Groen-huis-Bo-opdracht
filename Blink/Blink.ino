// HC-SR04 + buzzer
// Pinnen:
// TRIG  -> D2
// ECHO  -> D4
// BUZZER -> D13

const int trigPin = 2;
const int echoPin = 4;
const int buzzerPin = 13;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Trigger puls sturen
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo uitlezen
  duration = pulseIn(echoPin, HIGH);

  // Afstand berekenen (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Minder dan 7 cm
  if (distance < 7) {

    digitalWrite(buzzerPin, HIGH);
    delay(500);

    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  // Minder dan 20 cm
  else if (distance < 20) {

    digitalWrite(buzzerPin, HIGH);
    delay(100);

    digitalWrite(buzzerPin, LOW);
    delay(900);
  }

  // Verder dan 20 cm
  else {
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
}

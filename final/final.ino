#include "DHT.h"

#define DHTPIN 4      // Pinul digital 4 pentru senzorul DHT22
#define DHTTYPE DHT22 // Tipul senzorului DHT (DHT22)

#define MQ2pin A0     // Pinul pentru senzorul MQ2 (analogic, de exemplu A0)

DHT dht(DHTPIN, DHTTYPE);  // Creează un obiect pentru senzorul DHT

void setup() {
  Serial.begin(9600);    // Inițializează comunicația serială
  dht.begin();           // Inițializează senzorul DHT

  pinMode(2, INPUT);     // Setează pinul 2 pentru senzorul de foc
  pinMode(MQ2pin, INPUT); // Setează pinul MQ2 ca intrare
  Serial.println(1);      // Trimite cifra 1 la pornirea Arduino
}

void loop() {
  // Citirea senzorului MQ2
  float sensorValue = analogRead(MQ2pin);  // Citirea valorii analogice de pe senzorul MQ2
  if (sensorValue > 80) {
    Serial.println(3);  // Trimite cifra 3 dacă mirosul de gaz depășește 80
  }

  // Citirea senzorului de foc
  if (digitalRead(2) == 0) {   // Dacă senzorul de foc detectează foc
    Serial.println(2);          // Trimite cifra 2 pentru foc
  }

  // Citirea senzorului DHT22 (temperatură și umiditate)
  float humi = dht.readHumidity();    // Citirea umidității
  float tempC = dht.readTemperature(); // Citirea temperaturii în grade Celsius
  
  // Verificarea citirii senzorului DHT
  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");  // Dacă citirea eșuează
  } else {
    // Dacă umiditatea depășește 70%, trimitem cifra 4
    if (humi > 70) {
      Serial.println(4);
    }

    // Dacă temperatura depășește 40°C, trimitem cifra 5
    if (tempC > 40) {
      Serial.println(5);
    }
  }

  delay(2000);  // Așteaptă 2 secunde înainte de următoarea citire
}

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SI1145.h>

#define DHTPIN 2  // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11  // Definir el tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SI1145 sunlight = Adafruit_SI1145();

const int moisturePin = A0;  // Pin del sensor de humedad del suelo
const int buttonWritePin = 14;  // Pin del botón verde
const int buttonResetPin = 12;  // Pin del botón blanco

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  if (!sunlight.begin()) {
    Serial.println("Sensor de luz no encontrado");
    while (1);
  }

  pinMode(buttonWritePin, INPUT_PULLUP);
  pinMode(buttonResetPin, INPUT_PULLUP);
}

void loop() {
  // Si el botón blanco (reset) está presionado
  if (digitalRead(buttonResetPin) == LOW) {
    Serial.println("Datos eliminados");  // Solo una simulación, no puede borrar datos desde aquí.
  }

  // Si el botón verde está presionado
  if (digitalRead(buttonWritePin) == LOW) {
    // Obtener datos del sensor DHT11
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Obtener datos del sensor de luz solar
    uint16_t UV = sunlight.readUV() / 100;  // Valor UV
    uint16_t visible = sunlight.readVisible();  // Luz visible
    uint16_t IR = sunlight.readIR();  // Infrarrojo

    // Obtener datos del sensor de humedad del suelo
    int soilMoisture = analogRead(moisturePin);
    String soilMoistureStatus;
    if (soilMoisture < 300) {
      soilMoistureStatus = "dry";
    } else if (soilMoisture < 600) {
      soilMoistureStatus = "moist";
    } else {
      soilMoistureStatus = "wet";
    }

    // Enviar datos del sensor DHT11, sensor de luz y sensor de humedad del suelo por serial
    String dataString = String(temperature) + "," + String(humidity) + "," + String(UV) + "," + String(visible) + "," + String(IR) + "," + String(soilMoisture) + "," + soilMoistureStatus;
    Serial.println(dataString);

    delay(1000);  // Esperar un segundo antes de enviar los siguientes datos
  }
}

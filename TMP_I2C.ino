#include <Wire.h>

#define SDA = 2
#define SCL = 3

const uint8_t TMP117_ADDRESS = 0x48;  // I2C address of the TMP117 sensor

float readTemperature() {
  // Request temperature data from TMP117
  Wire.beginTransmission(TMP117_ADDRESS);
  Wire.write(0x00);  // Configuration register address
  Wire.endTransmission();
  
  // Read temperature data (2 bytes) from TMP117
  Wire.requestFrom(TMP117_ADDRESS, 2);
  
  // Combine the received bytes into a 16-bit signed integer
  uint16_t rawTemperature = (Wire.read() << 8) | Wire.read();
  
  // Convert raw temperature data to Celsius
  float temperature = rawTemperature * 0.0078125;
  
  return temperature;
}

void setup() {
  Wire.begin();  // Initialize I2C communication
  Serial.begin(115200);  // Initialize Serial communication
  delay(2000);  // Allow some time for initialization
}

void loop() {
  float temperature = readTemperature();  // Read temperature from TMP117 sensor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(1000);  // Delay between readings
}
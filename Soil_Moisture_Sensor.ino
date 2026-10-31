/*
  Soil Moisture Monitor
  Board: Arduino Uno
  Sensor: Analog soil moisture sensor

  Wiring:
    Sensor VCC -> 5V (use the voltage supported by your sensor)
    Sensor GND -> GND
    Sensor AO  -> A0

  The built-in LED indicates dry soil.
*/

const byte SOIL_SENSOR_PIN = A0;
const byte STATUS_LED_PIN = LED_BUILTIN;

// Calibrate these values for your own sensor and soil.
// Read the sensor in dry air/dry soil and in thoroughly wet soil.
// On many analog sensors, the dry reading is higher than the wet reading.
const int DRY_VALUE = 800;
const int WET_VALUE = 350;

const int DRY_THRESHOLD_PERCENT = 30;
const byte SAMPLE_COUNT = 10;

int readAverageMoistureRaw() {
  long total = 0;

  for (byte i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(SOIL_SENSOR_PIN);
    delay(10);
  }

  return total / SAMPLE_COUNT;
}

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println(F("Soil Moisture Monitor"));
  Serial.println(F("Calibrate DRY_VALUE and WET_VALUE for your sensor."));
}

void loop() {
  const int rawValue = readAverageMoistureRaw();

  // map() supports either sensor direction; constrain keeps the result in 0-100%.
  int moisturePercent = map(rawValue, DRY_VALUE, WET_VALUE, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  const bool soilIsDry = moisturePercent < DRY_THRESHOLD_PERCENT;
  digitalWrite(STATUS_LED_PIN, soilIsDry ? HIGH : LOW);

  Serial.print(F("Raw sensor value: "));
  Serial.print(rawValue);
  Serial.print(F(" | Estimated moisture: "));
  Serial.print(moisturePercent);
  Serial.print(F("% | Status: "));
  Serial.println(soilIsDry ? F("DRY - watering may be needed") : F("MOIST"));

  delay(1000);
}

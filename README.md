# Soil Moisture Monitoring System using Arduino

An Arduino Uno project that reads an analog soil-moisture sensor, estimates the soil moisture level as a percentage, and reports whether the soil is dry or moist through the Serial Monitor. The built-in LED turns on when the measured moisture is below the configured dry threshold.

## Features

- Reads the analog output of a soil-moisture sensor.
- Averages multiple readings to reduce small fluctuations.
- Converts the sensor reading into an estimated moisture percentage.
- Displays the raw sensor value, estimated percentage, and status in the Serial Monitor.
- Turns on the Arduino's built-in LED when the soil is classified as dry.
- Uses configurable calibration values and a configurable dry threshold.

## Components Required

- Arduino Uno (or a compatible Arduino board)
- Analog soil-moisture sensor with VCC, GND, and AO pins
- Jumper wires
- USB cable for programming and Serial Monitor output
- Soil and a container for testing

> This sketch uses the sensor's **analog output (AO)**. A digital-only sensor module is not suitable without modifying the wiring and code.

## Circuit Connections

| Soil-moisture sensor | Arduino Uno |
|---|---|
| VCC | 5V (or the voltage specified by your sensor) |
| GND | GND |
| AO | A0 |

The built-in LED is used as the dry-soil indicator, so no external LED is required.

## Repository Structure

```text
Soil-Moisture-Sensor-with-Arduino/
├── Soil_Moisture_Sensor.ino
└── README.md
```

## How It Works

1. The sensor produces an analog voltage that changes with the moisture around its probe.
2. Arduino reads the analog signal on pin A0. On an Arduino Uno, `analogRead()` normally returns a value from 0 to 1023.
3. The sketch takes 10 readings and calculates their average.
4. The average reading is mapped between the calibrated dry and wet readings to estimate a percentage from 0% to 100%.
5. If the estimated moisture is below the configured threshold, the built-in LED turns on and the Serial Monitor reports a dry-soil warning.
6. The process repeats every second.

**Important:** The percentage is an estimated, sensor-specific value, not a laboratory measurement of volumetric water content. Sensor response varies with sensor type, soil composition, packing, salinity, and supply voltage.

## Arduino IDE Setup

1. Connect the sensor to the Arduino using the wiring table above.
2. Open `Soil_Moisture_Sensor.ino` in the Arduino IDE.
3. Select **Arduino Uno** under **Tools → Board** and select the correct port.
4. Upload the sketch.
5. Open **Tools → Serial Monitor** and set the baud rate to **9600**.
6. Test the sensor in dry and moist soil and calibrate the values as described below.

## Calibration

The example sketch starts with these placeholder values:

```cpp
const int DRY_VALUE = 800;
const int WET_VALUE = 350;
const int DRY_THRESHOLD_PERCENT = 30;
```

These values are **examples, not universal sensor readings**. Calibrate your own sensor:

1. Upload the sketch and note the raw sensor value in dry soil (or the sensor's dry reference condition).
2. Place the sensor in thoroughly moist soil, wait for the reading to stabilize, and note the raw value.
3. Set `DRY_VALUE` to the dry reference reading and `WET_VALUE` to the moist reference reading.
4. Choose a suitable `DRY_THRESHOLD_PERCENT` for your plant and soil.
5. Upload the updated sketch and test again.

Many common analog modules produce a higher raw reading when dry and a lower reading when wet, but this is not guaranteed. The mapping in the sketch supports either direction as long as the two calibration values are correct and different.

## Example Serial Monitor Output

```text
Soil Moisture Monitor
Raw sensor value: 785 | Estimated moisture: 3% | Status: DRY - watering may be needed
Raw sensor value: 610 | Estimated moisture: 39% | Status: MOIST
Raw sensor value: 420 | Estimated moisture: 81% | Status: MOIST
```

*The readings above are illustrative only; your values will depend on your sensor and calibration.*

## Troubleshooting

- **No readings or a constant value:** Check the AO-to-A0 connection, power, and ground.
- **Percentage is always 0% or 100%:** Recheck calibration values and make sure `DRY_VALUE` and `WET_VALUE` are different.
- **Readings fluctuate:** Keep wiring secure, avoid touching the probe during measurement, and allow the sensor reading to stabilize.
- **LED behavior seems reversed:** Verify calibration and check whether your sensor's raw value increases or decreases as the soil dries.

## Future Improvements

- Add an LCD or OLED to display moisture locally.
- Add a buzzer or external status LED.
- Add a relay-controlled pump with appropriate driver circuitry and electrical protection.
- Add data logging or wireless monitoring using an ESP8266/ESP32.

> The current sketch does **not** control a water pump. Pump control should be added only with a correctly rated relay or MOSFET driver and suitable power isolation/protection.

## License

No license has been specified for this repository. Add a license file if you want to define how others may use, modify, and distribute this project.

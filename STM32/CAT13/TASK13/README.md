
# **README**

# Sensor Interfacing (BME280) – STM32 (Debug) – ESP8266 (Wi-Fi) HTTP – Node Analytics

## Experiment Details

**Project:** BME280 Sensor Interfacing and Environmental Monitoring

**Microcontroller:** STM32F410RB

**Sensor:** Bosch BME280

**Communication Protocol (Sensor):** I2C

**Wi-Fi Module:** Wemos D1 Mini (ESP8266)

**Communication Protocol (Network):** HTTP

**Development Environment:** STM32CubeIDE / Keil µVision

**Sensor Driver:** Bosch Sensortec BME280 Sensor API

**Analytics Platform:** Node-RED

---

## 1. Problem Statement

Develop an STM32-based environmental sensing application to interface a BME280 sensor using the I2C protocol and obtain compensated temperature, pressure, and humidity measurements.

The Bosch Sensortec BME280 Sensor API is used as the reference driver implementation.

The required driver files and compensation algorithms are sourced from the official Bosch Sensortec BME280 Sensor API repository.

**Official Repository:**

https://github.com/boschsensortec/BME280_SensorAPI

---

## 2. Objective

To interface the Bosch BME280 environmental sensor with the STM32 microcontroller using I2C communication and retrieve accurate temperature, pressure, and humidity measurements.

The project integrates sensor interfacing, Wi-Fi connectivity, HTTP communication, and Node-RED analytics to develop an environmental monitoring application.

---

## 3. Hardware Requirements

- STM32F410RB Development Board
- Bosch BME280 Environmental Sensor
- Wemos D1 Mini (ESP8266)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

---

## 4. Software Requirements

- STM32CubeIDE
- Keil µVision (if used)
- STM32 HAL Library
- Bosch Sensortec BME280 Sensor API
- ESP8266 AT Firmware
- Node-RED
- Web Browser

---

## 5. BME280 Sensor Overview

The BME280 is an environmental sensor capable of measuring three important parameters:

| Parameter | Description |
|---|---|
| Temperature | Measures ambient temperature |
| Pressure | Measures atmospheric pressure |
| Humidity | Measures relative humidity |

The sensor communicates with the STM32 microcontroller using the I2C protocol.

The Bosch Sensortec BME280 Sensor API provides the driver implementation and compensation algorithms required to obtain calibrated sensor measurements.

---

## 6. Sensor Interfacing Using I2C

### Objective

To establish I2C communication between the STM32F410RB and the BME280 sensor.

### Working Principle

The STM32 acts as the I2C master, while the BME280 operates as the I2C slave.

The microcontroller communicates with the sensor through the SDA and SCL lines.

The Bosch BME280 Sensor API is integrated into the STM32 project to initialize the sensor, configure its settings, and retrieve compensated measurement values.

### Implementation Steps

1. Configure the I2C peripheral in STM32CubeIDE.
2. Establish the I2C connection with the BME280 sensor.
3. Integrate the Bosch Sensortec BME280 Sensor API.
4. Implement the required I2C read and write functions.
5. Initialize the BME280 sensor.
6. Configure the sensor settings.
7. Trigger or read sensor measurements.
8. Retrieve compensated temperature, pressure, and humidity values.
9. Display the sensor measurements through the debugging interface.

---

## 7. Bosch Sensortec BME280 Sensor API

### Objective

To use the official Bosch Sensortec driver implementation for communicating with the BME280 sensor and obtaining compensated environmental measurements.

### API Integration

The official Bosch repository provides:

- Sensor driver implementation.
- Sensor configuration functions.
- Register read and write operations.
- Calibration data handling.
- Compensation algorithms.
- Temperature, pressure, and humidity measurement functions.

### Official Repository

https://github.com/boschsensortec/BME280_SensorAPI

### Important API Functions

| Function | Purpose |
|---|---|
| `bme280_init()` | Initialize the BME280 device |
| `bme280_set_sensor_settings()` | Configure sensor settings |
| `bme280_set_sensor_mode()` | Configure sensor operating mode |
| `bme280_get_sensor_data()` | Retrieve compensated sensor measurements |

*The exact function signatures and configuration parameters should follow the version of the Bosch Sensor API integrated into the project.*

---

## 8. Environmental Data Acquisition

### Objective

To continuously obtain environmental measurements from the BME280 sensor.

### Working Principle

After successful sensor initialization, the STM32 periodically reads the sensor measurements through I2C.

The Bosch Sensor API processes the raw sensor data using the calibration information and compensation algorithms.

The application obtains three compensated measurements:

1. Temperature
2. Atmospheric Pressure
3. Relative Humidity

### Expected Output

| Parameter | Unit |
|---|---|
| Temperature | °C |
| Pressure | hPa |
| Humidity | % RH |

The measurements are updated periodically and made available for further processing and transmission.

---

## 9. Project Architecture

The project integrates the following components:

1. **BME280 Sensor:** Measures environmental parameters.
2. **STM32F410RB:** Acquires sensor data and processes measurements.
3. **Wemos ESP8266:** Provides Wi-Fi connectivity.
4. **HTTP Communication:** Transfers environmental data over the network.
5. **Node-RED:** Receives and visualizes the environmental data.

### Communication Flow

```text
       BME280 SENSOR
              |
              | I2C
              v
        STM32F410RB
              |
              | UART
              v
        Wemos ESP8266
              |
              | Wi-Fi / HTTP
              v
          Node-RED
              |
              v
      Environmental
         Dashboard
```

---

## 10. Expected Results

1. Successfully establish I2C communication between STM32 and BME280.
2. Integrate the official Bosch Sensortec BME280 Sensor API.
3. Initialize and configure the BME280 sensor.
4. Retrieve compensated temperature measurements.
5. Retrieve compensated pressure measurements.
6. Retrieve compensated humidity measurements.
7. Establish communication between STM32 and ESP8266.
8. Transfer environmental measurements through Wi-Fi using HTTP.
9. Visualize the environmental measurements using Node-RED.

---

## 11. Concepts Covered

- STM32 microcontroller programming.
- I2C communication protocol.
- BME280 sensor interfacing.
- Bosch Sensortec Sensor API.
- Sensor initialization and configuration.
- Calibration and compensation algorithms.
- Temperature measurement.
- Atmospheric pressure measurement.
- Relative humidity measurement.
- UART communication.
- ESP8266 Wi-Fi connectivity.
- HTTP communication.
- Node-RED dashboard development.
- Environmental data acquisition and visualization.

---

## 12. Result

Successfully developed an STM32-based environmental sensing application using the Bosch BME280 Sensor API.

Established I2C communication with the BME280 sensor to obtain compensated temperature, pressure, and humidity measurements. The project architecture further integrates ESP8266 Wi-Fi connectivity, HTTP communication, and Node-RED for environmental data visualization.

---

## Deliverables

- STM32 I2C configuration.
- Bosch BME280 Sensor API integration.
- BME280 initialization and configuration.
- Temperature, pressure, and humidity acquisition.
- UART communication implementation.
- ESP8266 Wi-Fi integration.
- HTTP data transmission.
- Node-RED analytics and dashboard.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.

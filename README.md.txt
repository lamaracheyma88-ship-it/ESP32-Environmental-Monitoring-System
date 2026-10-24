# ESP32 Autonomous Environmental Monitoring System

## 1. Project Overview

The ESP32 Autonomous Environmental Monitoring System is an embedded systems project developed and tested using the Wokwi online simulator.

The system integrates multiple sensors to monitor environmental conditions, measure distance, detect motion, and estimate vibration-related changes using acceleration data.

Sensor readings are processed by the ESP32 and displayed on an OLED screen. When predefined alert conditions are detected, the system activates an LED and a buzzer to provide visual and audible warnings.

This project demonstrates the practical application of microcontroller programming, sensor integration, and threshold-based monitoring in an embedded system.

## 2. Project Objectives

The main objectives of this project are to:

- Monitor temperature and relative humidity.
- Measure distance using an ultrasonic sensor.
- Detect motion using a PIR sensor.
- Estimate vibration-related changes using an accelerometer.
- Display sensor readings and system status on an OLED screen.
- Implement threshold-based alert conditions.
- Control an LED and a buzzer in response to detected conditions.
- Practise embedded C++ programming using the ESP32.

## 3. Hardware Components

The following components are used in the simulation:

| Component | Function |
|---|---|
| ESP32 | Processes sensor data and controls the system. |
| DHT22 | Measures temperature and relative humidity. |
| HC-SR04 | Measures distance using ultrasonic waves. |
| PIR Motion Sensor | Detects movement. |
| MPU6050 | Measures acceleration and angular velocity; acceleration data is used for basic vibration estimation. |
| SSD1306 OLED Display | Displays sensor readings and system status. |
| LED | Provides a visual alert. |
| Buzzer | Provides an audible alert. |
| Resistor | Limits current through the LED. |
| Connecting Wires | Connect the components to the ESP32. |

## 4. Software and Development Tools

- Wokwi — Online electronic circuit and microcontroller simulator.
- Arduino Framework — Used to program the ESP32.
- C++ — Programming language used to implement the system logic.

### Libraries

The project uses the following libraries:

- Wire
- DHT
- Adafruit GFX
- Adafruit SSD1306
- Adafruit MPU6050
- Adafruit Unified Sensor, as required by the library dependencies.

## 5. System Operation

The ESP32 periodically reads sensor measurements and evaluates them against predefined threshold values.

The configured alert conditions include:

- Temperature above 35 °C.
- Relative humidity above 80%.
- Valid distance measurements below 30 cm.
- Motion detected by the PIR sensor.
- Acceleration deviation above the configured vibration threshold.

When at least one alert condition is detected:

- The LED flashes.
- The buzzer produces an audible warning.
- The OLED displays the sensor readings and alert status.
- The Serial Monitor reports the measurements and system status.

When no alert condition is detected, the system displays an OK status, turns off the LED, and stops the buzzer.

## 6. Simulation and Testing

The system was tested in the Wokwi simulation environment.

During testing, the LED activated and the buzzer produced sound in response to alert conditions. The simulation also supports observation of sensor readings through the OLED display and Serial Monitor.

These tests demonstrate the interaction between the ESP32, the connected sensors, and the output devices within the simulated environment.

The results represent simulation behavior and do not constitute physical hardware testing.
You can access the project simulation here:
[open the project on Wokwi](https://wokwi.com/projects/478526497631101953).

## 7. Project Files

The project includes the following files:

- wokwi :_ Contains the ESP32 source code, circuit diagram, library list, and Wokwi project configuration.
- media :_Contains the project video file.
- screenshots :_Contains code screenshots created using  Carbon and images documenting the Wokwi circuit and simulation results.
- README.md :_provides an overview of the project, its components, operation, and documentation.
- scribe links txt :_Contains links to the step-by-step project documentation.


## 8. Project Documentation
Project documentation is organized to support understanding of the circuit, source code, and development process.

The supporting materials include screenshots, code images, and development notes collected during the project.

Step-by-step documentation links are also available in Scribe-Links.txt.

## 9. Learning Outcomes

Through this project, I gained practical experience in:

- Programming the ESP32 using the Arduino framework.
- Integrating multiple sensors into one system.
- Reading temperature, humidity, distance, motion, and acceleration data.
- Working with I2C-compatible devices.
- Implementing threshold-based monitoring logic.
- Controlling visual and audible alert devices.
- Testing embedded system behavior using simulation tools.
- Organizing and documenting a technical project.

## 10. Future Improvements

Possible future improvements include:

- Building and testing a physical hardware prototype.
- Improving sensor error handling and measurement reliability.
- Adding data logging and historical measurement analysis.
- Developing a wireless interface for remote monitoring.
- Refining the vibration estimation method through further testing.

## 11. Conclusion

The ESP32 Autonomous Environmental Monitoring System combines environmental sensing, distance measurement, motion detection, basic vibration estimation, and alert generation within a single simulated embedded system.

The project provides practical experience in microcontroller programming, sensor integration, and technical documentation, while establishing a foundation for further development and physical implementation.

---

Project Type: Embedded Systems Simulation  
Microcontroller: ESP32  
Development Environment: Wokwi  
Programming Language: C++
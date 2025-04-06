# Air Quality Index Analyzer

A real-time indoor air quality monitoring system using the **LPC1768 microcontroller** and **MQ-135 gas sensor**, designed to provide a low-cost, accurate solution for detecting air pollutants and displaying the **Air Quality Index (AQI)** on a 16x2 LCD.

---

## Overview

This project detects and displays AQI based on levels of:

- Carbon Dioxide (CO₂)
- Ammonia (NH₃)
- Methane (CH₄)
- Volatile Organic Compounds (VOCs)

The system continuously samples data from the MQ-135 sensor, calculates the AQI, and displays it on a 16x2 LCD for real-time monitoring.

---

## Components

- **LPC1768** – ARM Cortex-M3 microcontroller
- **MQ-135** – Air quality sensor for gas detection
- **16x2 LCD** – For displaying AQI values
- **Supporting circuitry** – Resistors, jumper wires, breadboard

---

## Features

- Real-time AQI monitoring on LCD  
- Calibrated sensor readings for accuracy
- buzzer for alterting Dangerous AQI 
- Designed for indoor environments  
- Easily extensible (e.g., logging, alerts)

---

## Methodology

The project is structured into the following steps:

1. **Define LCD Control Pins**: Set up the RS (Register Select), EN (Enable), and DT (Data) pins to communicate with the LCD screen.

2. **Initialize LCD Display**: Configure the LCD using initialization commands to set cursor position, mode, etc.

3. **Initialize ADC**: Set up the LPC1768's built-in ADC to read analog data from the MQ-135 sensor.

4. **Read Sensor Data**: Acquire analog readings from the MQ-135 sensor using the ADC. This data represents the air quality level.

5. **Calculate AQI**: Convert the raw sensor readings into an AQI value using a formula or lookup table.

6. **Display AQI on LCD**: Show the calculated AQI and corresponding air quality description (e.g., "GOOD", "BAD", "DANGER") on the LCD.

7. **Buzzer Activation (Optional)**: If the AQI exceeds a certain threshold, activate a buzzer to alert users of high pollution levels.

8. **Repeat Process**: Continuously repeat the data reading, AQI calculation, and display update cycle to provide real-time monitoring.

9. **Error Handling**: Implement error detection for sensor failure or communication issues and take necessary corrective actions.

---

##Circuit Diagram
![image](https://github.com/user-attachments/assets/f979d0ad-3518-44f1-916a-a8d19f3aba92)


## Physical connections
![image](https://github.com/user-attachments/assets/d77e71fe-d58d-4958-8085-302f2aabca08)

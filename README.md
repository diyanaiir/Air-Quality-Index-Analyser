Air Quality Index Analyzer
A real-time indoor air quality monitoring system built using the LPC1768 microcontroller and the MQ-135 gas sensor. The project is designed to be low-cost, reliable, and easy to use, displaying the computed AQI on a 16x2 LCD.

Overview
This system detects common pollutants like carbon dioxide, ammonia, methane, and VOCs. Based on sensor readings, it calculates the Air Quality Index (AQI) and shows the result on an LCD screen. The goal is to create an accessible solution for monitoring air quality in enclosed environments like homes, offices, or hospitals.

Components Used
LPC1768 Microcontroller

MQ-135 Gas Sensor

16x2 LCD Display

Supporting circuitry (resistors, wires, breadboard, etc.)

Features
Real-time AQI monitoring

Simple LCD-based display

Sensor calibration for improved accuracy

Lightweight and portable setup

Potential for expansion (e.g., data logging, mobile alerts)

Setup Instructions
Connect MQ-135 sensor to LPC1768 (analog pin for gas data).

Interface the 16x2 LCD for AQI output display.

Flash the code onto LPC1768 using Keil or mbed IDE.

Power the board and observe AQI values in real time

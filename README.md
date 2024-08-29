# Scara Robot

## Overview
The SCARA (Selective Compliant Assembly Robot Arm) robot featured in this project is a simple yet effective tool for learning about robotic motion planning and control. This robot utilizes two servo motors to perform planar movements and demonstrates fundamental concepts of inverse kinematics and motion planning.

## Features
- **2 Servo Motors:** Provides control over the robot’s movement in a 2D plane.
- **Arduino Powered:** Uses an Arduino microcontroller to handle the control logic and servo commands.
- **Motion Planning:** Implemented algorithms for forward and inverse kinematics.
- **3D Model:** Includes a downloadable 3D model for visualizing and understanding the robot’s structure and movement.

## Hardware Requirements
- **Microcontroller**
- **2 Servo Motors**
- **Power Supply for Arduino**
- **Jumper Wires**
- **Breadboard (optional)**

## Software Requirements
- **Arduino IDE:** For uploading the code to the Arduino board.
- **Servo Library:** Included in the Arduino IDE, used to control the servo motors.

## Installation and Setup

### 1. Hardware Assembly
1. **Mount the Servo Motors:** Securely attach the servo motors to the robot’s base and arms.
2. **Connect the Servos:** Wire the servo motors to the Arduino board. Typically, the servo’s signal wires go to PWM-capable pins on the Arduino (B - GND / R - VCC / Y - SIGNAL).

### 2. Software Setup
1. **Download the Code:** Clone or download the repository containing the Arduino code.
2. **Install the Arduino IDE:** If you haven't already, download and install the Arduino IDE.
3. **Open the Code:** Open the `scaraRobot.ino` file in the Arduino IDE.
4. **Upload the Code:** Select your Arduino board type and port from the Tools menu and upload the code to the Arduino board.

## Usage
1. **Power On the System:** Ensure the power supply is connected and turn on the system.
2. **Run the Code:** The Arduino will start executing the code and control the servo motors based on the programmed instructions.
3. **Observe the Movements:** The SCARA robot should move according to the inverse kinematics calculations and motion planning defined in the code.

## Code Explanation
- **cinv():** cinve implements the inverse kinematics algorithms to calculate each angle base on x and y coordinates and arms length.
- **move():** move function is responsable to realize the motion planing across 2 points in space, utilizing acceleration and speed inputs.
- **drawRectangle():** this function utilizes move function to draw rectangles based on 2 points.

## 3D Model
A 3D model of the SCARA robot is available in this repository to help visualize the robot’s design and movement. You can download the model from the [3D Model folder](link-to-3D-model-folder).


## Contact
For any questions or inquiries, please contact [savictor3963@gmail.com](mailto:savictor3963@gmail.com).

---

Thank you for your interest in the SCARA robot project. We hope this helps you understand the basics of robotic motion planning and control!

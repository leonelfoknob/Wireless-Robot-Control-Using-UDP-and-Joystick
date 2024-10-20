# Wireless-Robot-Control-Using-UDP-and-Joystick

This project demonstrates how to wirelessly control a robot (MFX1) using a Rampage RMX23 Cockpit USB Vibrating Joystick. The joystick commands are sent over a local network using the UDP protocol, and received on an Arduino via another computer( Jetson, Latte panda, Raspberry pi... ) , which then forwards the data to the robot for control. The system allows seamless control without physical connection, leveraging a Python script for the communication.

- Current Setup
    - Joystick Control: The Rampage RMX23 joystick is used with the Pygame library to capture and map the user’s commands.
    - Data Transmission: The commands are transmitted over a 5GHz Wi-Fi network using UDP protocol. The data is first sent to a receiving computer, which then forwards it to an Arduino         via a   serial connection.
    - Robot Integration: The system is integrated into the MFX1 robot, allowing full remote control, though challenges arise with Wi-Fi latency over 1m.
      Future Improvements

  One issue observed is the drop in connection speed and increasing latency when operating over 1m on a 5GHz Wi-Fi connection. Future work will focus on improving network stability,        potentially by increasing Wi-Fi signal strength or switching to a different communication technology. Open to suggestions for improving wireless range and reducing latency.

## How It Works

1. Joystick Command Mapping
    The Rampage RMX23 Cockpit joystick is read using Pygame.
    Each input (button press, joystick movement) is mapped to a specific command.

3. Data Transmission Over UDP
    A Python script on the sending side captures the joystick data and sends it to the IP address of the receiving machine over UDP.

5. Arduino Integration with Robot
    The Arduino processes the commands received over the serial connection, map its to a specific command (forward, backward, turn, etc.) and sends control signals to the MFX1 robot's         motors,leds...
    The robot reacts accordingly, performing the movements specified by the joystick input.

7. Testing on MFX1 Robot
    The initial test with an Arduino and LCD to verify communication was successful.
    The system was then integrated into MFX1, achieving effective remote control within 1m, though latency became an issue beyond that range.

## Files Included

    Joystick Command Mapping Code (Python): Captures joystick input and sends commands over UDP.
    Receiver Code (Python): Receives the UDP packets and forwards them to Arduino via serial communication.
    Arduino Code: Reads the serial data and translates it into movement commands for the robot.
    MFX1 Robot Control Code: Demonstrates real-time robot control using the joystick and UDP communication.

## Diagram and other support
A full system diagram will be shared, detailing the communication between components (Joystick, computer, Wi-Fi, Arduino, and MFX1 robot).

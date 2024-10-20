# Wireless-Robot-Control-Using-UDP-and-Joystick

This project demonstrates how to wirelessly control a robot (MFX1) using a Rampage RMX23 Cockpit USB Vibrating Joystick. The joystick commands are sent over a local network using the UDP protocol, and received on an Arduino via another computer( Jetson, Latte panda, Raspberry pi... ) , which then forwards the data to the robot for control. The system allows seamless control without physical connection, leveraging a Python script for the communication.

- Current Setup
    - Joystick Control: The Rampage RMX23 joystick is used with the Pygame library to capture and map the user’s commands. Ysou can find more details : https://github.com/leonelfoknob/Rampage-RMX23-Cockpit-Joystick-and-Pygame-library
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

## Setup Instructions
To get this project running and control the MFX1 robot (or Arduino for testing purposes) using a joystick over a local network with UDP, follow the steps below:

1. Setup the Receiver Side (Robot/Arduino)
    - Connect your robot (MFX1) or Arduino to the receiver computer (the one that will decode the joystick commands).
    - Upload the appropriate code:
        - For MFX1 robot control, upload the mfx1_controled_by_rampage_over_udp.ino file to the Arduino onboard the MFX1 robot.
        - For testing with an LCD, upload the receive_and_decode_joystick_command.ino file to an Arduino connected to an LCD screen. This will help verify joystick commands are being                received and decoded correctly.
    - Modify the joystick_command_receive_via_udp.py file:
        - Change the COM port to match your Arduino's port (on Windows, it might look like COM3; on Linux, something like /dev/ttyUSB0).
        - Set the baud rate to match the one you’re using in the Arduino code (e.g., 9600).
        - Update the IP address and port in the Python code to the IP address and port of the receiver computer where the Arduino is connected.

2. Setup the Sender Side (Joystick/Command)
    - On a separate computer (which will send joystick commands):
        - Connect the joystick (Rampage RMX23 Cockpit USB Vibrating Joystick) to this machine.
    - Modify the joystick_command_send_via_udp.py file:
        - Update the IP address and port in the code to match the IP and port of the receiver computer where the Arduino or MFX1 robot is connected.
    - Run the Python script on this computer: joystick_command_send_via_udp.py.
3. Running the System
    - Ensure both computers (sender and receiver) are connected to the same Wi-Fi network.
    - First, on the receiver side, run the joystick_command_receive_via_udp.py script. This will start listening for incoming joystick commands.
    - Next, on the sender side, run the joystick_command_send_via_udp.py script. This will begin sending joystick commands over the network to the receiver.
    - If using the LCD for testing, you will see joystick inputs reflected on the screen. For the robot, it should start responding to joystick movements.


## Diagram and other support
A full system diagram will be shared, detailing the communication between components (Joystick, computer, Wi-Fi, Arduino, and MFX1 robot).
![sistem_diyagram](https://github.com/user-attachments/assets/b2941541-2131-4563-9b52-b46bf975e0e4)

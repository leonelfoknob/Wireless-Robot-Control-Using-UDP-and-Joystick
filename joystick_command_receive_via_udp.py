import socket
import datetime
import pickle
import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 9600)  # Replace 'COM3' with your Arduino's port
time.sleep(2)  # Wait for serial connection to establish

#UDP_IP = "127.0.0.1"#lookup
UDP_IP = "192.168.1.32" #my ip adress MakinaFleo WİFİ
#UDP_IP = "192.168.1.7" #my ip adress robotic_lab WİFİ
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
 
while True:
    data, addr = sock.recvfrom(1024)
    if data:
        date_time = datetime.datetime.now()
        date_time = str(date_time)
        commands = pickle.loads(data)
        # Convert commands dictionary to a comma-separated string
        command_str = ','.join([str(commands[key]) for key in commands]) + '\n'
        ser.write(command_str.encode())  # Send to Arduino
        time.sleep(0.1)  # Slow down the loop for stability
        print(commands)
        #print(str(commands[1]))
        #print("received message: %s" % commands + "my time = " + date_time)

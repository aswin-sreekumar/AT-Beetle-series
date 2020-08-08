# blueBase 1.0 controller software
# from ASIMOV TECHNOLOGIES
# designed and developed by ASWIN SREEKUMAR

import time
import getpass
import serial
import serial.tools.list_ports
import bluetooth
from pynput import keyboard
import sys

while True:         #initialising the program and authentication
    print("blueBase controller 1.0 : Powered by ASIMOV TECHNOLOGIES")
    time.sleep(0.5)
    print("Authentication")
    time.sleep(0.5)
    username=input("Username : ")
    password=getpass.getpass(prompt='Password : ',stream=None)
    time.sleep(0.5)
    if(username=="asimovtech" and password=="beetleseries"): #username - asimovtech : password - beetleseries
        print("Authentication successful .....")
        time.sleep(0.5)
        print("Initialising command center .....")
        time.sleep(0.5)
        print("Configuring Ycon packages .....")
        time.sleep(0.5)
        print("Initialisation successful ......")
        time.sleep(0.5)
        break
    else:
        print("Authentication failure")

m=0

while True:             # COM port number input
    choice=input("Enter COM port :")
    if(choice.isnumeric()):
        com='COM'+choice
        print("Establishing connection ...")
        break
    else:
        print("Invalid COM port")

bt_path=serial.Serial()         #connecting to COM port
bt_path.baudrate=9600
bt_path.port=com
try:
    bt_path.open()
except:
    bt_path.close()
    sys.stdout.flush()

if(bt_path.isOpen()):
    print("Connection established ....")
    print("Controller ready to rage")
else:
    print("ERROR : Couldn't open COM port")
    bt_path.close()
    sys.stdout.flush()
    exit()

def dir_press(key):                         #function for character transmission on key press
    global m
    vk = key.vk if hasattr(key, 'vk') else key.value.vk
    if(vk==27):
        bt_path.write(bytes('S','utf-8')) #ESC key
        return False
    elif(vk==38):
        bt_path.write(bytes('F','utf-8')) #up
        m=1
    elif(vk==40):
        bt_path.write(bytes('B','utf-8')) #down
        m=2
    elif(vk==37):               #left
        if(m==1):
            bt_path.write(bytes('G','utf-8'))       # up+left
        elif(m==2):
            bt_path.write(bytes('H','utf-8'))       #down+left
        else:
            bt_path.write(bytes('L','utf-8'))       #left
    elif(vk==39):
        if(m==1):
            bt_path.write(bytes('I','utf-8'))       #up+right
        elif(m==2):
            bt_path.write(bytes('J','utf-8'))       #down+right
        else:
            bt_path.write(bytes('R','utf-8'))       #right

def dir_release(key):
    global m
    vk = key.vk if hasattr(key, 'vk') else key.value.vk
    if(vk==38):
        bt_path.write(bytes('S','utf-8'))       #up
        m=0
    elif(vk==40):
        bt_path.write(bytes('S','utf-8'))       #down
        m=0
    elif(vk==37):
        if(m==1):
            bt_path.write(bytes('F','utf-8'))   #up
        elif(m==2):
            bt_path.write(bytes('B','utf-8'))   #down
        else:
            bt_path.write(bytes('S','utf-8'))   #stop
    elif(vk==39):
        if(m==1):
            bt_path.write(bytes('F','utf-8'))   #up
        elif(m==2):
            bt_path.write(bytes('B','utf-8'))   #down
        else:
            bt_path.write(bytes('S','utf-8'))   #stop
    sys.stdout.flush()

with keyboard.Listener(on_press=dir_press,on_release=dir_release) as listener:
    listener.join()                 #listen for key strokes and releases

print("Controller closed ...")
print("blueBase terminated ...")
bt_path.close()             #close COM port
sys.stdout.flush()          #flush buffer values

# blueBase 2.0 controller software
# from ASIMOV TECHNOLOGIES
# designed and developed by ASWIN SREEKUMAR

import time
import getpass
import serial
import serial.tools.list_ports
import bluetooth
from pynput import keyboard
import sys

while True:                 #initialising program and authentication
    print("blueBase controller 2.0 : Powered by ASIMOV TECHNOLOGIES")
    time.sleep(0.5)
    print("Authentication")
    time.sleep(0.5)
    username=input("Username : ")
    password=getpass.getpass(prompt='Password : ',stream=None)
    time.sleep(0.5)
    if(username=="asimovtech" and password=="beetleseries"):
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

while True:                 # COM port input
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

def battery_levels():                   #receiving char from bot and display corresponding battery level
    bt_path.write(bytes('b','utf-8'))
    data=bt_path.read()                 #receiving char
    data=str(data,'utf-8')
    if(data=='1'):
        battery_lvl='100'
    elif(data=='2'):
        battery_lvl='95'
    elif(data=='3'):
        battery_lvl='85'
    elif(data=='4'):
        battery_lvl='70'
    elif(data=='5'):
        battery_lvl='55'
    elif(data=='6'):
        battery_lvl='30'
    elif(data=='7'):
        battery_lvl='10'
    elif(data=='8'):
        battery_lvl='5'
    else:
        battery_lvl='0'
    print("Battery level :",battery_lvl, "%")
    if(battery_lvl=="10"):
        print("WARNING : RUNNING OUT OF POWER")
    elif(battery_lvl=="5" or battery_lvl=="0"):
        print("BOT SHUTDOWN DUE TO INSUFFICIENT POWER")

def dir_press(key):
    global m,charge,b
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
    elif(vk==37):
        if(m==1):
            bt_path.write(bytes('G','utf-8'))       #up+left
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
    elif(vk==66):
        battery_levels()
        sys.stdout.flush()

def dir_release(key):
    global m
    vk = key.vk if hasattr(key, 'vk') else key.value.vk
    if(vk==38):
        bt_path.write(bytes('S','utf-8')) #stop
        m=0
    elif(vk==40):
        bt_path.write(bytes('S','utf-8')) #stop
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
    listener.join()     #listening for key strokes and releases

print("Controller closed ...")
print("blueBase terminated ...")
bt_path.close()         #closing COM port
sys.stdout.flush()      #flushing buffer memory

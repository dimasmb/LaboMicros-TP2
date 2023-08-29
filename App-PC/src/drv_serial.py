import sys
import glob
import serial
from serial.tools import list_ports


def open_serial(COM_num, baud):
    ser = serial.Serial(COM_num, baud, timeout=0, rtscts=1)
    # s = ser.read(100)

def close_serial():
    ser.close()

def search_ports():
    ports = list_ports.comports()
    return ports


# port=search_ports()
# ser = serial.Serial(port[0].name, timeout=3)
# print(ser.read())
# ser.close()
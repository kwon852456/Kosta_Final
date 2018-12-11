from socket import *
from select import select
import sys
import serial
import time
import threading

port='/dev/ttyUSB0' 
baudrate=9600
se = serial.Serial(port,baudrate)
print("conn sucessed ")

#  HOST = '192.168.0.106'
#  PORT = 56789
#  BUFSIZE = 1024
#  ADDR = (HOST, PORT)
#
#  clientSocket = socket(AF_INET, SOCK_STREAM)

#  try:
    #  clientSocket.connect(ADDR)
#
#
#  except Exception as e:
    #  print("error!")
    #  sys.exit()

def serialRead():
    while True :
        print("serialRead()...")
        if se.readable():
            byteStr = se.readline()
            data = byteStr.decode()
            date = data[:len(data)-1]
            print("data : %s " % data)    


def serialWrite():
    print("serialWrite()...")
    se.write('1'.encode())
    time.sleep(1)

readThread = threading.Thread(target=serialRead)
readThread.start()
while True:
    serialWrite()

    #  clientSocket.send(num)
    #  data=clientSocket.recv(BUFSIZE)
    #  print(data.decode())
    #  print("serial wrote")
    #  data2 = se.readline()
    #  print("data 2 :")
    #  print(data2.decode())



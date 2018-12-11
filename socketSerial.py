#-*- coding: utf-8 -*-
from socket import *
from select import select
import sys
import serial
import time
import threading
import select

port='/dev/ttyUSB0'  
baudrate=115200
se = serial.Serial(port,baudrate)

def empty_socket(sock):
    """remove the data present on the socket"""
    input = [sock]
    while 1:
        inputready, o, e = select.select(input,[],[], 0.0)
        if len(inputready)==0: break
        for s in inputready: s.recv(1)

def mkServSocket() :

    global serverSocket

    print("conn sucessed ")

    HOST = '192.168.0.118'
    PORT = 12345
    BUFSIZE = 1024
    ADDR = (HOST, PORT)

    serverSocket = socket(AF_INET, SOCK_STREAM)
    serverSocket.bind(ADDR)
    serverSocket.listen(10)

    clientSocket, addr_info = serverSocket.accept()
    print("clientSocket created...")
    return clientSocket

def serialRead():
    while True :
        if se.readable():
            byteStr = se.readline()
            data = byteStr.decode()
            print("data from serial : %s " % data)    


def serialWrite(location):
    print("serialWrite()...")
    se.write(location)

BUFSIZE = 1024
clientSocket = mkServSocket()
readThread = threading.Thread(target=serialRead)
readThread.start()
while True:
    print("onWhile....")
    data=clientSocket.recv(BUFSIZE)
    empty_socket(clientSocket)
    #  print("data from soc : %s " % data.decode())
    #  data2 = unicode(data,'utf-8').encode('utf-8')
    #  print("data from soc : %s " % data)

    serialWrite(data)
    print("endWhile....")

    #  clientSocket.send(num)
    #  data=clientSocket.recv(BUFSIZE)
    #  print(data.decode())
    #  print("serial wrote")
    #  data2 = se.readline()
    #  print("data 2 :")
    #  print(data2.decode())



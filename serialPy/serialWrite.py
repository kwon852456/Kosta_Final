
import serial
from time import sleep

print("arduino serial")

port='/dev/ttyUSB0'  #메 뉴 >  도 구>  시리얼포 트
baudrate=9600
se = serial.Serial(port,baudrate)

while True:	
        print("input num:")
        #  var = input()
        num = '2'
        se.write(num.encode())
        #  se.write(var.encode())
        se.flush()
        sleep(0.5)

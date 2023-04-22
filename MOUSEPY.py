import  sys
import time 
import serial
import pyautogui

from win32api import GetSystemMetrics                         


time.sleep(2)
w=GetSystemMetrics(0)
h=GetSystemMetrics(1)
print("Width =", GetSystemMetrics(0))
print("Height =", GetSystemMetrics(1))
pyautogui.moveTo(w/2,h/2)
posx=w/2
posy=h/2
while True:
   try:
      ArduinoSerial=serial.Serial('com3',115200,timeout = 0.1)
      ArduinoSerial.flushInput()
      cc=str(ArduinoSerial.readline().decode("utf-8")).strip('\n').strip('\r')
      str2=cc.split(",")
      #print(str2)
      if(len(str2)>1):
         x=int(float(str2[0])*100)
         y=int(float(str2[1])*100)
         print(x,y)
         posx+=y
         posy+=x
         #print(posx,posy)
         pyautogui.moveTo(posx,posy)
         print(str2[2])
         
         if(str2[3]==str(1)):
            if(str2[2]==str(0)):
               pyautogui.scroll(-80)
            else:
               pyautogui.scroll(80)
         elif(str2[2]==str(1)):
            pyautogui.doubleClick()
      ArduinoSerial.close()
   except:
      pass
   


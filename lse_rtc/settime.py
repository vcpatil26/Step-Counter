#!virt/bin/python

from serial import Serial, SerialException
from datetime import datetime, time, date

class Timesetter:
    def __init__(self,port="/dev/ttyUSB0",baud=9600):
         try:
             print "Try STM32 on port =",port
             self.ser = Serial(port,baud,timeout=3)
         except SerialException:
             print "Error: could not open %s" % port
             exit()
         except:
             print "Device not found \n"
             exit()
         pass

    def sendtime(self):
        print "Waiting for @ symbol from STM32\n"
        line = self.ser.readline()
        while (line != "@\n"):
            line = self.ser.readline()
            print line.rstrip('\n')
        print "Symbol Received\n"
        dt = datetime.now()
        t = dt.timetuple()
        year = t[0]
        month = t[1]
        day = t[2]
        hour = t[3]
        minute = t[4] 
        second = t[5]
        timestr = "%d,%d,%d,%d,%d,%d\n\r"%(hour, minute, second, month, day, year)
        print timestr
        self.ser.write(timestr)
        self.ser.flush()
        while (1):
            line = self.ser.readline()
            print line.rstrip('\n')
  

#        print timestr 
            
         
if __name__ == "__main__":
    ts = Timesetter();
    ts.sendtime();

import socket
import time
HOST = "192.168.50.50" # The remote host
PORT = 30003 # The same port as used by the server
print "Starting Program"
count = 0
while (count < 1):
 s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 s.connect((HOST, PORT))
 time.sleep(0.5)
 print "Set output 1 and 2 high"
 s.send ("set_digital_out(1,True)" + "\n")

 
 s.send("set_digital_out(2,True)" + "\n")
 time.sleep(2)
 print "Robot starts Moving to 3 positions based on joint positions"

 s.send ("movej([-1.95, -1.58, 1.16, -1.15, -1.55, 1.18], a=1.0, v=0.1)" + "\n")
 time.sleep(10)


 s.send ("movej([-1.95, -1.66, 1.71, -1.62, -1.56, 1.19], a=1.0, v=0.1)" + "\n")
 time.sleep(10)
 
 s.send ("movej([-1.96, -1.53, 2.08, -2.12, -1.56, 1.19], a=1.0, v=0.1)" + "\n")
 time.sleep(10)


 time.sleep(1)
data = s.recv(1024)
s.close()
print ("Received", repr(data))
print "Status data received from robot"


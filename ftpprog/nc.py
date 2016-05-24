#File: ftpClient.py
#Author: Max Grubb
#Date: 3/7/2016
#Description: Client side of ftp for basic files

import os, sys
from socket import *  

#Argument check
length = len(sys.argv)
if (length < 5):
	print 'Usage: python ftpClient.py <serveraddr> <serverport> <operation> OR <operation and filename> <localport>'
        sys.exit()	

#Set local port and name
HOST = gethostbyname(gethostname())   
PORT = int(sys.argv[length-1]) 

#Set string for command sent to client

counter = 3
clientMessage = sys.argv[3]
counter = counter + 1
while (counter < length):
	clientMessage = clientMessage + ' ' + sys.argv[counter] 
	counter = counter + 1

#Client connection to server for command
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((sys.argv[1], int(sys.argv[2])))
clientSocket.send(clientMessage)

#Set up listening connection for data transfer
grubbServ = socket(AF_INET, SOCK_STREAM)
print 'Data connection set'
 

try:
    grubbServ.bind((HOST, PORT))
except socket.error as msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
print 'Socket Bound'
 
#Start listening on socket
grubbServ.listen(2)
 
conn, addr = grubbServ.accept()
print 'Connected with ' + addr[0] + ':' + str(addr[1])
print 'Downloading'

#Loop for directory/file commands
if length == 6:

	ftpFile = open(sys.argv[4],'w')
	while True:
		serverMessage = conn.recv(1024)
		ftpFile.write(serverMessage)
		if serverMessage == 'err':
			print 'File ' + sys.argv[4] + ' does not exist'
			clientSocket.close()
			grubbServ.close()
			os.remove(sys.argv[4])
			sys.exit()
		elif serverMessage == "":
			print "Operation Complete\n"
			ftpFile.close()
			clientSocket.close()
			grubbServ.close()
			sys.exit()
	#	else:
	#		print "Operation Complete\n"
	#		ftpFile.close()
	#		clientSocket.close()
	#		grubbServ.close()
	#		sys.exit()
elif (length < 6):

	while True:
		serverMessage = conn.recv(1024)
		print serverMessage
		if serverMessage == "":
			print "Operation Complete\n"
			grubbServ.close()
			clientSocket.close()	
			sys.exit()
	
     

#ECS 152A Project 1
#Project Group: Ari Schoenfeld, Richard Gao

from socket import *
from datetime import datetime, timedelta
from time import time

clientSocket = socket(AF_INET, SOCK_DGRAM)

serverName = 'localhost'
serverPort = 12000

clientSocket.settimeout(1)

days = ['M','T','W','R','F','S','U']
weekDay = datetime.today().weekday()


for i in range(1,11):
	try:
		message = 'Ping ' + str(i)
		messagePrint = message  + str(datetime.now().strftime(" %Y-%m-%d ")) + str(days[weekDay]) + str(datetime.now().strftime(" %H:%M")) 
		print messagePrint
		sendTime = time()
		clientSocket.sendto(message,(serverName,serverPort))

		reply, addr = clientSocket.recvfrom(1024)
		replyTime = time()
		replyPrint = reply + str(datetime.now().strftime(" %Y-%m-%d ")) + str(days[weekDay]) + str(datetime.now().strftime(" %H:%M"))
		print replyPrint
		print('RTT: {0:.3f}\n'.format((replyTime-sendTime)*1000))

	except timeout:
		print 'Request timed out\n'

clientSocket.close()

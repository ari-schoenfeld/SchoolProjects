# client
from socket import *
import os
serverName = input('What is the server IP address? ')
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
message = 'blank'
print('Socket {} opened to server {}:{}'.format(clientSocket.fileno(), serverName, serverPort))
while message != 'exit':
	message = input('What is your message? ')
	clientSocket.send(str.encode(message))
	if message != 'exit':
		response = clientSocket.recv(1024)
		print('Server reply: {}'.format(bytes.decode(response)))
clientSocket.close()

#server
import os
from socket import *
from multiprocessing import Process

serverPort = 12000
listeningSocket = socket(AF_INET, SOCK_STREAM)
listeningSocket.bind(('', serverPort))
listeningSocket.listen(1)
print('Server ready, socket {} listening on localhost: {}'.format(listeningSocket.fileno(), serverPort))
message = 'blank'
while 1:
	connectionSocket, addr = listeningSocket.accept()
	pid = os.fork()
	if pid !=0:
		connectionSocket.close()
		continue

	listeningSocket.close();

	while message !='exit':
		message = connectionSocket.recv(1024)
		if message !='exit':
			print('Message received: {} from IP {}:{}'.format(str.encode(message), addr[0], addr[1]))
			connectionSocket.send(str.encode(message))
		if bytes.decode(message) =='exit':
			connectionSocket.close()
	os._exit(0)

import socket
import os
from _thread import *

ServerSocket = socket.socket()
host = '192.168.24.126'
port = 10000

distance = -1

try:
    ServerSocket.bind((host, port))
except socket.error as e:
    print(str(e))

print('Waiting for a Connection...')
ServerSocket.listen(5)

def threaded_client(connection):
    # connection.send(str.encode('Welcome to the Server\n'))
    while True:
        global distance
        data = connection.recv(2048).decode('utf-8')
        if data.startswith('distance=') :
            distance = int(data[9:-1])
            print('distance=' + str(distance))
            reply = "ACK\n"
        if data.startswith('GET') :
            if distance < 20 :
                reply = "0\n"
            elif distance < 50 :
                reply = "1\n"
            else:
                reply = "2\n"
        if not data:
            break
        connection.sendall(reply.encode('utf-8'))
    connection.close()

while True:
    Client, address = ServerSocket.accept()
    print('Connection from: ' + address[0] + ':' + str(address[1]))
    start_new_thread(threaded_client, (Client, ))
ServerSocket.close()


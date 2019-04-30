#! /usr/bin/python

import socket
import sys

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 9090))

for arg in sys.argv[1:]:
    client.send(arg + "\n")

client.send("\n")

while True:
    response = client.recv(1024)
    if not response:
        break
    print(response)

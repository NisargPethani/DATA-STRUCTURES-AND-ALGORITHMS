import socket
import ast
import json
import inspect

def stub(n):
	ip = '127.0.0.22'
	port = 50002

	sock=socket.socket()
	sock.connect((ip,port))

	fun_name = inspect.stack()[1][3]

	msg = [1, fun_name, n]
	sock.send(str(msg).encode())
	
	msg = sock.recv(1024).decode()
	
	sock.close()
	return msg

def get_string(n):
	return stub(n)

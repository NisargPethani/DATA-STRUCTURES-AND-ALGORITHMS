import socket
import json
import random
import string 
import time

def start_sensor(sensor_no):
    json_file = open("sensor_server.json")
    dict = json.load(json_file)     

    sensor_serv_ip = dict["ip"]
    sensor_serv_port = dict["port"]

    while True:
        sock = socket.socket()
        sock.connect((sensor_serv_ip, sensor_serv_port))

        time.sleep(5)

        random_str = ''.join(random.choices(string.ascii_uppercase + string.digits, k = 8)) 
        
        msg = [-5, [sensor_no, random_str]]
        msg = str(msg)

        print("Random genrated string: ",random_str)
        print("String sent to server")

        sock.sendall(msg.encode())
        recv_msg = sock.recv(1024).decode()

        print("Server reply: ",recv_msg)
        print()

if __name__ == "__main__":

    sensor_no = int(input("Enter Sensor This No to start sensor : "))
    start_sensor(sensor_no)
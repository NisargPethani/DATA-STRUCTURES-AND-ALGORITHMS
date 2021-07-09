import socket
import json
import threading
import ast

serv_ip = ''
serv_port = -1

sensor_dict = {

}

def serve_req(client_sock, addr):

    recv_msg = client_sock.recv(1024).decode()
    recv_msg = ast.literal_eval(recv_msg)

    msg_type = recv_msg[0]
    msg = recv_msg[1]

    if msg_type == -5:
        sensor_no = msg[0]
        my_string = msg[1]
        # print("Updated my_string : ",my_string)
        
        if sensor_no in sensor_dict.keys():
            sensor_dict[sensor_no] = sensor_dict[sensor_no] + my_string
        else:
            sensor_dict[sensor_no] = my_string

        sock = socket.socket()
        sock.connect((serv_ip, serv_port))
        
        snd_msg = [2, "Want msg"]
        snd_msg = str(snd_msg)

        sock.send(snd_msg.encode())
        recv_msg = sock.recv(1024).decode()

        recv_msg = ast.literal_eval(recv_msg)        

        print(recv_msg[1])
        print("Appended to", str(sensor_no) + "'s string : ", my_string)
        print()

        recv_msg_type = recv_msg[0]

        if recv_msg_type == 5:
            recv_sensor_no = int(recv_msg[2])
        
        recv_msg = recv_msg[1]

        if recv_msg_type == 5:
            if recv_sensor_no in sensor_dict.keys():
                msg = sensor_dict[recv_sensor_no]
                sensor_dict[recv_sensor_no] = ''
            else:
                msg = 'Invalid Sensor No'

            sock.sendall(msg.encode())
            sock.recv(1024).decode()

        sock.close()

        client_reply_msg = [1, "Received str: " + my_string]
        client_reply_msg = str(client_reply_msg)

        client_sock.sendall(client_reply_msg.encode())
        
    client_sock.close()    

def start_sensor_server():

    json_file = open("sensor_server.json")
    dict = json.load(json_file)     

    sensor_serv_ip = dict["ip"]
    sensor_serv_port = dict["port"]

    s = socket.socket()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((sensor_serv_ip, sensor_serv_port))

    s.listen(10)

    print("Sensor Server started")
    print("Started listening\n\n")

    while True:

        client_sock, addr = s.accept()
        threading.Thread(target=serve_req, args=(client_sock, addr,)).start() 

if __name__ == "__main__":

    json_file = open("serv.json")
    dict = json.load(json_file)     

    serv_ip = dict["ip"]
    serv_port = dict["port"]

    start_sensor_server()
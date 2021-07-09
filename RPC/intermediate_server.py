import socket
import threading
import ast
import inspect
import time
import json

def get_string(recv_no):    

    global sensor_serv_flag
    global rpc_flag
    global my_string
    global sensor_no

    sensor_no = recv_no
    
    sensor_serv_flag = True
    rpc_flag = True

    while rpc_flag == True:
        time.sleep(0.5)

    rpc_flag = True
    return my_string

def serve_req(client_sock, addr):

    global rpc_flag
    global sensor_serv_flag
    global my_string
    global sensor_no

    msg = client_sock.recv(1024).decode()
    msg_chunks = ast.literal_eval(msg)

    msg_type = msg_chunks[0]
    msg = msg_chunks[1]

    if msg_type == 1:

        fun_name = msg
        arg = str(msg_chunks[2])
        print("Client Has requested for string")
        rval = eval(fun_name + "("+ arg +")")

        client_sock.sendall(rval.encode())

    elif msg_type == 2:
        if sensor_serv_flag == True:
            sensor_serv_flag = False
            
            reply_msg = [5, "YES", sensor_no]
            reply_msg = str(reply_msg)

            client_sock.sendall(reply_msg.encode())
            my_string = client_sock.recv(1024).decode()

            rpc_flag = False

            reply_msg = [1, "Got msg"]
            reply_msg = str(reply_msg)

            client_sock.sendall(reply_msg.encode())

        elif sensor_serv_flag == False:
            sensor_serv_flag = False
            
            reply_msg = [6, "NO"]
            reply_msg = str(reply_msg)

            client_sock.sendall(reply_msg.encode())

    client_sock.close()

def main():
    
    json_file = open("serv.json")
    dict = json.load(json_file)     

    ip = dict["ip"]
    port = dict["port"]

    s=socket.socket()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((ip,port))

    s.listen(10)

    print("Server started")
    print("Started listening\n\n")

    while True:
        client_sock, addr = s.accept()
        threading.Thread(target=serve_req, args=(client_sock, addr,)).start() 

if __name__ == "__main__":

    global rpc_flag
    global sensor_serv_flag
    global my_string
    global sensor_no

    my_string = ''

    rpc_flag = True
    sensor_serv_flag = False
    sensor_no = -1

    main()


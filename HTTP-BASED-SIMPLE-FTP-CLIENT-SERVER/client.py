import socket

cmd = input("Enter Command: ")
if(cmd[:3] == "GET"):

    input = cmd[4:].lstrip().rstrip()

    ip = "127.0.0.1"
    port = 50003

    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("socket created")

    s.connect((ip,port))
    print("Connection Established\n\n")

    header = "HTTP/1.1 /"+input+" OK\n\n"
    s.send(header.encode()) 

    header=s.recv(256).decode()
    header=header.split("\n\n")[0].split("\r\n")

    if(len(header)==3):
        file_name = header[2].split(" ")[2].split("=")[1]

        f=open(file_name,"wb")
        t=s.recv(1024)
        while(len(t)==1024):
            f.write(t)
            t=s.recv(1024)    

        f.write(t)
        f.close()

        print("File received : "+file_name)
    else:
        print("File Not Exist")

    s.close()
else:
    print("Wrong Command")

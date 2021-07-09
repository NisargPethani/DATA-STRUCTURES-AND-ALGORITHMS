import socket
import threading

content_type_html = "text/html"
content_type_txt = "text/plain"
content_type_mp3 = "audio/mpeg"
content_type_pdf = "application/pdf"

def serve_req(client_sock, addr):

    print("Connection addr : "+str(addr))
    
    try:
        recv_msg = client_sock.recv(1024).decode('utf8')
        file_addr = recv_msg.split("\r\n")[0].split()[1]
        print("File: " + file_addr)

        # File
        file=open(file_addr[1:] ,"rb")
        file_data=file.read()
        file.close()

        file_name = file_addr.split('/')[2]
        file_ext = file_name[-3:]
        
        if(file_ext == "mp3"):
            content_type = content_type_mp3
        elif(file_ext == "pdf"):
            content_type = content_type_pdf
        else:
            content_type = content_type_txt

        # Header
        header = "HTTP/1.1 200 OK\r\nContent-Type: "+content_type+"\r\nContent-Disposition: attachment; filename="+file_name+"\n\n"
        header = "{:<256}".format(header)
        client_sock.send(header.encode())
        
        # File
        client_sock.send(file_data) 

    except Exception: 

        content_type = content_type_html

        # Header
        header = "HTTP/1.1 200 OK\r\nContent-Type: "+content_type+"\n\n"
        header = "{:<256}".format(header)
        client_sock.send(header.encode()) 

        msg = "<h1>File Not Exist</h1>" 
        client_sock.send(msg.encode()) 

    client_sock.close()

def main():
    ip = "127.0.0.1"
    port = 50003

    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("socket created")

    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    s.bind((ip,port))
    print("Bind info : "+str(ip)+":"+str(port))

    s.listen(10)
    print("Listen success\n\n")

    thread_count = 0
    while True:

        thread_count+=1
        print("New Thread created, Thread-count:"+str(thread_count))

        client_sock, addr = s.accept()
        threading.Thread(target=serve_req, args=(client_sock, addr,)).start() 

if __name__ == "__main__":
    main()


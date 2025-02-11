import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
server_socket.bind(('localhost', 4444))
print(socket.gethostbyname(socket.gethostname()))

while True:
    data, client_address = server_socket.recvfrom(1024)
    print(f"Получены данные от {client_address}: {data}")
 
server_socket.close()
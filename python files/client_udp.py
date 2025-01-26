import socket
# Создаем сокет
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

i=0
with open('C:/Users/денис/Desktop/Project/System-of-calling/data/days.txt', 'r') as f:
    a = f.read().split(', ')    

while True:
    # Отправляем данные серверу
    if i+1==len(a):
        i=0
    i+=1
    client_socket.sendto(bytes(a[i-1], encoding='utf-8'), ('172.20.10.3', 1234))

 
# Закрываем сокет
client_socket.close()
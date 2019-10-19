//
// Created by 蒋为 on 2019/10/14.
//

#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
class Server{
public:
    Server();
    ~Server();
    Server(const Server &)=delete;
    Server &operator=(const Server&)= delete;
    void WaitForClient();

private:
    int server_sock;
    int client_sock;
    struct sockaddr_in server_addr;
};

#endif //SOCKET_SERVER_H

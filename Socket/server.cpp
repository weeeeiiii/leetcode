//
// Created by 蒋为 on 2019/10/14.
//

#include "server.h"
#include <iostream>
#include <pthread.h>

struct socket_info{
    struct sockaddr_in sktaddr;
    int fd;
};
socket_info soc[1000];
int i=0;
socket_info connskt;
void *serverForClient(void *arg);                    //为对话的客户端进行服务的函数
pthread_t pt;

void thread(int clnt_sock,char file_name[])
{
    FILE *fq;
    int len;
    char response[1024]= {0};
    char  buffer[1024];
    char type[20];
    char file_path[1024]="/Users/wei/CLionProjects/Socket/资源/";
    strcat(file_path,file_name);                   //初始化

    if( ( fq = fopen(file_path,"rb") ) == NULL ){
        fq=fopen("/Users/wei/CLionProjects/Socket/资源/404.html","rb");
        fseek(fq, 0, SEEK_END);
        long lfilelen = ftell(fq);
        fseek(fq, 0, SEEK_SET);
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: text/html\r\nContent-length:%ld\r\n\r\n", lfilelen);
        write(clnt_sock,response, strlen(response));
        bzero(buffer,sizeof(buffer));
        while(!feof(fq)){
            len = fread(buffer, 1, sizeof(buffer), fq);
            if(len != write(clnt_sock, buffer, len)){
                printf("write.\n");
                break;
            }
        }
        return;
    }
    for(int i=0;i<strlen(file_name);i++)           //文件存在，则提取文件的类型
    {
        if(file_name[i]=='.')
        {
            i++;
            int xiabiao=0;
            while(i<strlen(file_name))
            {
                type[xiabiao++]=file_name[i];
                i++;
            }
            type[xiabiao]='\0';
            break;
        }
    }
    fseek(fq, 0, SEEK_END);
    long lfilelen = ftell(fq);
    fseek(fq, 0, SEEK_SET);
    if(strcmp(type,"png")==0||strcmp(type,"jpg")==0)
    {
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: image/png\r\nContent-length:%ld\r\n\r\n", lfilelen);
    }
    else if(strcmp(type,"html")==0)
    {
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: text/html\r\nContent-length:%ld\r\n\r\n", lfilelen);
    }
    else if(strcmp(type,"js")==0)
    {
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: application/x-javascript\r\nContent-length:%ld\r\n\r\n", lfilelen);
    }
    else if(strcmp(type,"ico")==0)
    {
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: image/x-icon\r\nContent-length:%ld\r\n\r\n", lfilelen);
    }
    else if(strcmp(type,"css")==0)
    {
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: text/css\r\nContent-length:%ld\r\n\r\n", lfilelen);
    }
    else if(strcmp(type,"mp3")==0)
    {
        sprintf(response, "HTTP/1.1 200 OK\r\nConnection:keep-alive\r\nETag: W/\"68789-1493185830000\r\nContent-Type: audio/mp3\r\nContent-length:%ld\r\n\r\n", lfilelen);
    }
    else
    {
        printf("%s没有找到\n",file_name);
        return ;
    }
    write(clnt_sock,response, strlen(response));
//    printf("%s\n", response);              //打印response
    bzero(buffer,sizeof(buffer));
    while(!feof(fq)){
        len = fread(buffer, 1, sizeof(buffer), fq);
        if(len != write(clnt_sock, buffer, len)){
            printf("write.\n");
            break;
        }
    }
    fclose(fq);
}

Server::Server() {
    if( (server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(1);
    }
    printf("----Init socket----\n");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(80);
    //设置端口可重用
    int contain;
    setsockopt(server_sock,SOL_SOCKET, SO_REUSEADDR, &contain, sizeof(int));

    //链接socket
    if( bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    printf("----Bind success----\n");

    //开始监听
    if( listen(server_sock, 1000) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    printf("----waiting to connect----\n");
}

Server::~Server() {
    close(server_sock);
    printf("----Close socket----\n");
}

void Server::WaitForClient()
{
    while(1)
    {
        signal(SIGPIPE, SIG_IGN);
        socklen_t clit_size= sizeof(connskt.sktaddr);
        connskt.fd = accept(server_sock, (struct sockaddr*)&connskt.sktaddr, &clit_size);   //接收新的请求
        if(connskt.fd<0)
        {
            if(errno==EINTR) continue;
            printf("accept error\n");
            exit(0);
        }

        memcpy(&soc[i],&connskt, sizeof(connskt));         //这里需要将收到的请求存到数组中，线程并不等于进程
        pthread_create(&pt,NULL,serverForClient,(void*)&soc[i++]);     //将数组作为参数
    }
}

void *serverForClient(void *arg)
{
    socket_info *connskt=(socket_info*) arg;
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    if(read(connskt->fd,buff, sizeof(buff)-1)<0)
    {
        printf("----read----\n");
        exit(1);
    }
    printf("get a client ,ip is %s,port is %d\n",inet_ntoa((*connskt).sktaddr.sin_addr),ntohs((*connskt).sktaddr.sin_port));
    printf("HTTP请求命令行：%s",buff);

    char file_name[100]={'\0'};        //提取浏览器索要的文件
    int xiabiao=0,i=0;
    if(strlen(buff)==0)
    {
        return 0;
    }
    for(i=0;i<strlen(buff);i++)
    {
        if(buff[i]=='/')
        {
            i++;
            break;
        }
    }
    while(1)
    {
        if(buff[i]==' ')
        {
            file_name[i+1]='\0';
            break;
        }
        file_name[xiabiao++]=buff[i++];
    }
    if(strlen(file_name)==0)
    {
        sprintf(file_name,"welcome.html");
    }
    thread(connskt->fd,file_name);
    thread(connskt->fd,file_name);
    printf("%s文件发送成功\n\n",file_name);
}
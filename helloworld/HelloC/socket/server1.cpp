//
//  server1.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/25.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  unix socket 服务器 fork
//  向每个连接服务器的客户端发送"hello client"
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace socket_server1 {

ssize_t readn(int fd, void *buff, size_t n) {
    ssize_t m = 0;
    while (m < n) {
        ssize_t len = read(fd, (char *)buff + m, n - m);
        if (len < 0) {
            perror("read failed.\n");
            return -1;
        }
        m += len;
    }
    
    return n;
}

ssize_t writen(int fd, void *buff, size_t n) {
    ssize_t m = 0;
    while (m < n) {
        ssize_t len = write(fd, (char *)buff + m, n - m);
        if (len < 0) {
            perror("write failed.\n");
            return -1;
        }
        m += len;
    }
    
    return n;
}

int main(int argc, const char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed.\n");
        return -1;
    }
    
    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9090);
    
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        perror("bind failed.\n");
        return -1;
    }
    
    if (listen(server_fd, 5) != 0) {
        perror("listen failed.\n");
        return -1;
    }
    
    while (true) {
        socklen_t addr_len = 0;
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("accept failed.\n");
            return -1;
        }
        
        pid_t pid = fork();
        if (pid < 0) {
            perror("fock failed.\n");
        } else if (pid == 0) {
            char buffer[] = "hello client";
            writen(client_fd, buffer, sizeof(buffer));
            close(client_fd);
            close(server_fd);
            return 0;
        }
    }
    
    return 0;
}

}

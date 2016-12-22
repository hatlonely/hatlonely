//
//  server2.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/25.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  unix socket 服务器 select
//  向每个连接服务器的客户端发送"hello client"
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace socket_server2 {

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
    
    int client[FD_SETSIZE];
    for (int i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;
    }
    fd_set allset;
    FD_ZERO(&allset);
    FD_SET(server_fd, &allset);
    int max_fd = server_fd;
    int maxi = 0;
    
    while (true) {
        fd_set rset = allset;
        int nready = select(max_fd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0) {
            perror("select failed.\n");
            return -1;
        }
        
        if (FD_ISSET(server_fd, &rset)) {
            socklen_t len = 0;
            int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
            if (client_fd < 0) {
                perror("accept failed.\n");
            }
            
            int i = 0;
            for (; i < FD_SETSIZE; i++) {
                if (client[i] == -1) {
                    client[i] = client_fd;
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                perror("too many clients");
                return -1;
            }
            FD_SET(client_fd, &allset);
            if (max_fd < client_fd) {
                max_fd = client_fd;
            }
            if (maxi < i) {
                maxi = i;
            }
            
            if (--nready <= 0) {
                continue;
            }
        }
        
        for (int i = 0; i <= maxi; i++) {
            int client_fd = client[i];
            if (client_fd < 0) {
                continue;
            }
            if (FD_ISSET(client_fd, &rset)) {
                char buffer[] = "hello client";
                writen(client_fd, buffer, sizeof(buffer));
                close(client_fd);
                
                FD_CLR(client_fd, &allset);
                client[i] = -1;
                
                if (--nready <= 0) {
                    break;
                }
            }
        }
    }
    
    return 0;
}

}

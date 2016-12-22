//
//  client.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/28.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

namespace socket_client {

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
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed.\n");
        return -1;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9090);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        perror("connect failed.\n");
        return -1;
    }
    
    char buffer[] = "hello server";
    writen(sock, buffer, sizeof(buffer));
    read(sock, buffer, sizeof(buffer));
    printf("get message from server [%s]\n", buffer);
    
    return 0;
}
    
}
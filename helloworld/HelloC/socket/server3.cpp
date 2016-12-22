//
//  server3.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/25.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  unix socket 服务器 poll
//  向每个连接服务器的客户端发送"hello client"
//
//  poll和select两者的机制相同，没有本质区别，同样存在一个缺点就是，
//  包含大量文件描述符的数组被整体复制于用户态和内核的地址空间之间，
//  而不论这些文件描述符是否就绪，它的开销随着文件描述符数量的增加而线性增大
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

namespace socket_server3 {
    
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
    
    struct pollfd client[OPEN_MAX];
    client[0].fd = server_fd;
    client[0].events = POLLRDNORM;
    for (int i = 1; i < OPEN_MAX; i++) {
        client[i].fd = -1;
    }
    int maxi = 0;
    
    while (true) {
        int nready = poll(client, maxi + 1, -1);
        if (nready < 0) {
            perror("poll failed.\n");
            return -1;
        }
        
        if (client[0].revents & POLLRDNORM) {
            socklen_t len = 0;
            int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
            if (client_fd < 0) {
                perror("accept failed.\n");
            }

            int i = 1;
            for (; i < OPEN_MAX; i++) {
                if (client[i].fd < 0) {
                    client[i].fd = client_fd;
                    client[i].events = POLLRDNORM;
                    break;
                }
            }
            if (i == OPEN_MAX) {
                printf("too many clients");
                return -1;
            }

            if (maxi < i) {
                maxi = i;
            }

            if (--nready <= 0) {
                continue;
            }
        }

        for (int i = 1; i <= maxi; i++) {
            int client_fd = client[i].fd;
            if (client_fd < 0) {
                continue;
            }
            if (client[i].revents & (POLLRDNORM | POLLERR)) {
                char buffer[] = "hello client";
                writen(client_fd, buffer, sizeof(buffer));
                close(client_fd);
                client[i].fd = -1;
                
                if (--nready <= 0) {
                    break;
                }
            }
        }
    }
    
    return 0;
}

}

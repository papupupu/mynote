# epoll中的ET和LT
## 情景
你是一个c++技术专家
## 提问
epoll的ET和LT有什么区别吗，可以给出代码例子解释一下吗



## 回答


epoll是Linux下的一种高效的I/O多路复用机制，可以同时监控多个文件描述符的状态，当其中任意一个文件描述符就绪时，就会通知应用程序进行相应的处理。在epoll中，有两种工作模式：ET（边缘触发）和LT（水平触发）。

ET模式下，当一个文件描述符从未就绪变为就绪时，epoll_wait函数会返回该文件描述符，应用程序需要立即处理该文件描述符，否则下次epoll_wait函数不会再次返回该文件描述符。ET模式下需要使用非阻塞IO。

LT模式下，当一个文件描述符就绪时，epoll_wait函数会返回该文件描述符，应用程序需要处理该文件描述符，否则下次epoll_wait函数还会返回该文件描述符。

下面是一个简单的示例代码，演示了ET和LT模式的区别：

```c++
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_EVENTS 10
#define BUF_SIZE 1024

void setnonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void do_epoll(int listen_fd, int epoll_fd, int flag) {
    struct epoll_event event, events[MAX_EVENTS];
    int nfds = 0, n = 0;
    char buf[BUF_SIZE];

    memset(&event, 0, sizeof(event));
    event.data.fd = listen_fd;
    event.events = EPOLLIN | flag;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event);

    while (1) {
        nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listen_fd) {
                int conn_fd = accept(listen_fd, NULL, NULL);
                if (conn_fd == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                setnonblocking(conn_fd);
                memset(&event, 0, sizeof(event));
                event.data.fd = conn_fd;
                event.events = EPOLLIN | flag;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &event);
            } else {
                int fd = events[n].data.fd;
                int len = read(fd, buf, BUF_SIZE);
                if (len == -1) {
                    if (errno != EAGAIN) {
                        perror("read");
                        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                        close(fd);
                    }
                } else if (len == 0) {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                } else {
                    write(STDOUT_FILENO, buf, len);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int listen_fd = 0, epoll_fd = 0;
    struct sockaddr_in serv_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_fd, SOMAXCONN) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    do_epoll(listen_fd, epoll_fd, EPOLLET); // ET模式
    // do_epoll(listen_fd, epoll_fd, 0); // LT模式

    close(listen_fd);
    close(epoll_fd);

    return 0;
}
```

在上面的代码中，我们使用了两个函数：setnonblocking和do_epoll。

setnonblocking函数用于将文件描述符设置为非阻塞模式。

do_epoll函数用于创建epoll实例，并将监听的文件描述符添加到epoll实例中。在循环中，我们使用epoll_wait函数等待文件描述符就绪，并处理就绪的文件描述符。在ET模式下，我们使用EPOLLET标志将文件描述符添加到epoll实例中。在LT模式下，我们不使用EPOLLET标志。

在ET模式下，当一个文件描述符从未就绪变为就绪时，epoll_wait函数会返回该文件描述符，应用程序需要立即处理该文件描述符，否则下次epoll_wait函数不会再次返回该文件描述符。在LT模式下，当一个文件描述符就绪时，epoll_wait函数会返回该文件描述符，应用程序需要处理该文件描述符，否则下次epoll_wait函数还会返回该文件描述符。

#

## 提问
请告诉我为什么pipe在linux不会出现互斥
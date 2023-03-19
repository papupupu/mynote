[toc]
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

# pipe在linux不会出现互斥是因为内核缓冲区
## 提问
请告诉我为什么pipe在linux不会出现互斥

## 回答


在Linux中，管道（pipe）是一种进程间通信（IPC）机制，它允许一个进程将输出发送到另一个进程的输入。管道是一种半双工通信方式，即数据只能在一个方向上流动，而且只能由一个进程写入，另一个进程读取。

管道不会出现互斥的原因是因为它是基于内核缓冲区的，而不是用户空间的缓冲区。当一个进程向管道写入数据时，数据会被存储在内核缓冲区中，而不是直接传递给另一个进程。当另一个进程从管道中读取数据时，数据也会从内核缓冲区中读取，而不是直接从写入进程的缓冲区中读取。

因此，多个进程可以同时向管道写入数据，而不会出现互斥的情况。当多个进程同时向管道写入数据时，内核会按照一定的规则将数据存储在缓冲区中，并且保证数据的顺序不会被打乱。另一个进程从管道中读取数据时，也会按照一定的规则从缓冲区中读取数据，并且保证数据的顺序不会被打乱。

因此，管道不会出现互斥的原因是因为它是基于内核缓冲区的，而不是用户空间的缓冲区，多个进程可以同时向管道写入数据，而不会出现互斥的情况。

# 为什么在内核缓冲区就不会出现互斥现象呢
## 提问
为什么在内核缓冲区就不会出现互斥现象呢

## 回答


在内核缓冲区中，访问和修改数据的操作都是由内核来完成的，而不是由用户程序直接进行的。因此，内核可以通过使用锁和其他同步机制来确保对缓冲区的访问是互斥的，从而避免了互斥现象的发生。此外，内核缓冲区的访问通常是以原子操作的方式进行的，这也有助于避免并发访问时的竞争条件和数据不一致问题。

# 所以pipe是利用了锁和其他的同步机制吗，如果是，是哪些
## 提问
所以pipe是利用了锁和其他的同步机制吗，如果是，是哪些


## 回答


是的，pipe利用了锁和其他的同步机制来实现进程间通信。

具体来说，pipe使用了以下同步机制：

1. 互斥锁：pipe中的读写操作需要互斥地进行，以避免多个进程同时读写同一个管道造成数据混乱。因此，pipe使用了互斥锁来保证读写操作的互斥性。

2. 条件变量：当管道中没有数据可读时，读进程需要等待写进程向管道中写入数据。为了避免读进程一直忙等待，pipe使用了条件变量来实现读进程的等待和唤醒。

3. 缓冲区：pipe中使用了缓冲区来存储数据，以避免读写进程之间的直接交互。缓冲区的大小可以通过参数进行设置，以满足不同的需求。

综上所述，pipe利用了互斥锁、条件变量和缓冲区等同步机制来实现进程间通信。

# 互斥锁，条件变量，原子操作
## 提问
写出上面你提到的三种同步机制的简单的代码例子
## 回答


1. 互斥锁

```c++
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void print(int num) {
    mtx.lock();
    std::cout << "Thread " << num << " is printing." << std::endl;
    mtx.unlock();
}

int main() {
    std::thread t1(print, 1);
    std::thread t2(print, 2);
    t1.join();
    t2.join();
    return 0;
}
```

2. 条件变量

```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print(int num) {
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready) {
        cv.wait(lock);
    }
    std::cout << "Thread " << num << " is printing." << std::endl;
}

int main() {
    std::thread t1(print, 1);
    std::thread t2(print, 2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ready = true;
    cv.notify_all();
    t1.join();
    t2.join();
    return 0;
}
```

3. 原子操作

```c++
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> count(0);

void increment() {
    for (int i = 0; i < 1000000; ++i) {
        count++;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Count: " << count << std::endl;
    return 0;
}
```

#
## 提问

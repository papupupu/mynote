Question:

请使用C++的面向对象思想，写一个ET模式，非阻塞监听，超时返回的epoll反应堆模型

Answer:

很高兴能够为您提供帮助！以下是一个基于C++的ET模式，非阻塞监听，超时返回的epoll反应堆模型示例：

```c++
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>

#define MAX_EVENTS 32
#define MAX_BUFFER_SIZE 1024

class EventLoop {
public:
    EventLoop(std::string address, int port) :
        address_(address), port_(port) {
            // 初始化 socket
            listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
            if (listen_fd_ < 0) {
                std::cerr << "Error: socket() failed." << std::endl;
                exit(EXIT_FAILURE);
            }

            // 绑定 socket
            sockaddr_in server_address;
            memset(&server_address, 0, sizeof(server_address));
            server_address.sin_family = AF_INET;
            server_address.sin_addr.s_addr = inet_addr(address_.c_str());
            server_address.sin_port = htons(port_);

            int ret = bind(listen_fd_, (sockaddr*)&server_address, sizeof(server_address));
            if (ret < 0) {
                std::cerr << "Error: bind() failed." << std::endl;
                exit(EXIT_FAILURE);
            }

            // 设置为非阻塞 socket
            int flags = fcntl(listen_fd_, F_GETFL, 0);
            flags |= O_NONBLOCK;
            ret = fcntl(listen_fd_, F_SETFL, flags);
            if (ret < 0) {
                std::cerr << "Error: fcntl() failed." << std::endl;
                exit(EXIT_FAILURE);
            }

            // 开始监听
            ret = listen(listen_fd_, SOMAXCONN);
            if (ret < 0) {
                std::cerr << "Error: listen() failed." << std::endl;
                exit(EXIT_FAILURE);
            }

            std::cout << "Server listening on " << address_ << ":" << port_ << std::endl;
        }

    ~EventLoop() {
        close(epoll_fd_);
        close(listen_fd_);
    }

    void Start() {
        epoll_event event;
        event.data.fd = listen_fd_;
        event.events = EPOLLIN | EPOLLET;
        AddEvent(event);

        std::vector<epoll_event> events(MAX_EVENTS);
        std::cout << "Waiting for incoming connections..." << std::endl;

        while (true) {
            int num_events = epoll_wait(epoll_fd_, &events[0], MAX_EVENTS, -1);
            if (num_events < 0) {
                std::cerr << "Error: epoll_wait() failed." << std::endl;
                break;
            }

            for (int i = 0; i < num_events; ++i) {
                if (events[i].data.fd == listen_fd_) {
                    OnAccept();
                }
                else {
                    if (events[i].events & EPOLLIN) {
                        OnRead(events[i].data.fd);
                    }
                    else if (events[i].events & EPOLLOUT) {
                        OnWrite(events[i].data.fd);
                    }
                }
            }
        }
    }

private:
    int listen_fd_;
    int epoll_fd_;
    std::string address_;
    int port_;

    bool AddEvent(epoll_event event) {
        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, event.data.fd, &event);
        if (ret < 0) {
            std::cerr << "Error: epoll_ctl() failed." << std::endl;
            return false;
        }
        return true;
    }

    bool ModifyEvent(epoll_event event) {
        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, event.data.fd, &event);
        if (ret < 0) {
            std::cerr << "Error: epoll_ctl() failed." << std::endl;
            return false;
        }
        return true;
    }

    bool DeleteEvent(epoll_event event) {
        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, event.data.fd, &event);
        if (ret < 0) {
            std::cerr << "Error: epoll_ctl() failed." << std::endl;
            return false;
        }
        return true;
    }

    void OnAccept() {
        while (true) {
            sockaddr_in client_address;
            socklen_t client_address_len = sizeof(client_address);
            int client_fd = accept(listen_fd_, (sockaddr*)&client_address, &client_address_len);
            if (client_fd < 0) {
               

<hr/>


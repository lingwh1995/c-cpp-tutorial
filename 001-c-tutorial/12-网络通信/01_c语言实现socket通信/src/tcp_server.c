#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

/**
 * TCP 服务端
 *
 * gcc tcp_server.c -o tcp_server
 */
int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char server_message[BUFFER_SIZE] = {0};

    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置socket选项，允许重用端口和地址
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定socket到指定端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接请求，最大等待队列长度为5
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 接受客户端连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    printf("Enter messages to send (type 'exit' to quit)\n");

    while (1)
    {
        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);
        memset(server_message, 0, BUFFER_SIZE);

        // 接收客户端消息
        ssize_t valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread < 0)
        {
            perror("read failed");
            break;
        }
        else if (valread == 0)
        {
            printf("Client disconnected\n");
            break;
        }

        printf("Client: %s\n", buffer);

        // 检查客户端是否发送了退出命令
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Client requested exit\n");
            break;
        }

        // 从控制台读取服务端要发送的消息
        printf("Server: ");
        if (fgets(server_message, BUFFER_SIZE, stdin) == NULL)
        {
            perror("fgets failed");
            break;
        }

        // 移除fgets添加的换行符
        server_message[strcspn(server_message, "\n")] = '\0';

        // 检查服务端是否输入了退出命令
        if (strcmp(server_message, "exit") == 0)
        {
            send(new_socket, server_message, strlen(server_message), 0);
            break;
        }

        // 发送消息给客户端
        send(new_socket, server_message, strlen(server_message), 0);
    }

    // 关闭连接
    close(new_socket);
    close(server_fd);
    printf("Server closed\n");

    return 0;
}
#endif

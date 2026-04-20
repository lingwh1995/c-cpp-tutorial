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
#define SERVER_IP "127.0.0.1"  // 服务器IP地址，本地测试用回环地址

/**
 * TCP 客户端
 *
 * gcc tcp_client.c -o tcp_client
 */
int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char client_message[BUFFER_SIZE] = {0};

    // 创建socket文件描述符
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将IPv4地址从文本转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
    {
        perror("invalid address/address not supported");
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", SERVER_IP, PORT);
    printf("Enter messages to send (type 'exit' to quit)\n");

    while (1)
    {
        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);
        memset(client_message, 0, BUFFER_SIZE);

        // 从控制台读取客户端要发送的消息
        printf("Client: ");
        if (fgets(client_message, BUFFER_SIZE, stdin) == NULL)
        {
            perror("fgets failed");
            break;
        }

        // 移除fgets添加的换行符
        client_message[strcspn(client_message, "\n")] = '\0';

        // 检查客户端是否输入了退出命令
        if (strcmp(client_message, "exit") == 0)
        {
            send(sock, client_message, strlen(client_message), 0);
            break;
        }

        // 发送消息给服务器
        send(sock, client_message, strlen(client_message), 0);

        // 读取服务器的响应
        ssize_t valread = read(sock, buffer, BUFFER_SIZE);
        if (valread < 0)
        {
            perror("read failed");
            break;
        }
        else if (valread == 0)
        {
            printf("Server disconnected\n");
            break;
        }

        printf("Server: %s\n", buffer);

        // 检查服务器是否发送了退出命令
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Server requested exit\n");
            break;
        }
    }

    // 关闭连接
    close(sock);
    printf("Client closed\n");

    return 0;
}
#endif

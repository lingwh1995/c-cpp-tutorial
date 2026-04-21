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
#define SERVER_IP "127.0.0.1"  // 服务器IP地址

/**
 * UDP 服务端
 *
 * gcc udp_client.c -o udp_client
 */
int main()
{
    int sockfd;
    char buffer[BUFFER_SIZE];
    char client_message[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    // 创建UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // 配置服务器地址信息
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // 将IPv4地址从文本转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr) <= 0)
    {
        perror("invalid address/address not supported");
        exit(EXIT_FAILURE);
    }

    printf("UDP Client connecting to %s:%d\n", SERVER_IP, PORT);
    printf("Enter messages to send (type 'exit' to quit)\n");

    socklen_t len = sizeof(servaddr);

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

        // 移除换行符
        client_message[strcspn(client_message, "\n")] = '\0';

        // 发送消息到服务器
        sendto(sockfd, (const char *)client_message, strlen(client_message),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

        // 检查是否要退出
        if (strcmp(client_message, "exit") == 0)
        {
            break;
        }

        // 接收服务器的响应
        ssize_t n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                             MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        if (n < 0)
        {
            perror("recvfrom failed");
            break;
        }
        buffer[n] = '\0';

        printf("Server: %s\n", buffer);

        // 检查服务器是否发送退出命令
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Server requested exit\n");
            break;
        }
    }

    // 关闭socket
    close(sockfd);
    printf("Client closed\n");

    return 0;
}
#endif

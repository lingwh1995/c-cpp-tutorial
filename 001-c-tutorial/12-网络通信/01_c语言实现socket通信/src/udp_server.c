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
 * UDP 服务端
 *
 * gcc udp_server.c -o udp_server
 */
int main()
{
    int sockfd;
    char buffer[BUFFER_SIZE];
    char server_message[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;

    // 创建UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // 配置服务器地址信息
    servaddr.sin_family = AF_INET;  // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;  // 绑定到所有可用接口
    servaddr.sin_port = htons(PORT);  // 端口号

    // 绑定socket到指定端口
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", PORT);
    printf("Enter messages to send (type 'exit' to quit)\n");

    socklen_t len = sizeof(cliaddr);  // 客户端地址长度

    while (1)
    {
        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);
        memset(server_message, 0, BUFFER_SIZE);

        // 接收客户端消息
        ssize_t n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                             MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        if (n < 0)
        {
            perror("recvfrom failed");
            break;
        }
        buffer[n] = '\0';

        // 显示客户端IP和端口以及收到的消息
        printf("Client %s:%d: %s\n", inet_ntoa(cliaddr.sin_addr),
               ntohs(cliaddr.sin_port), buffer);

        // 检查是否收到退出命令
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Client requested exit\n");
            break;
        }

        // 从控制台读取服务器要发送的消息
        printf("Server: ");
        if (fgets(server_message, BUFFER_SIZE, stdin) == NULL)
        {
            perror("fgets failed");
            break;
        }

        // 移除换行符
        server_message[strcspn(server_message, "\n")] = '\0';

        // 检查服务器是否输入退出命令
        if (strcmp(server_message, "exit") == 0)
        {
            sendto(sockfd, (const char *)server_message, strlen(server_message),
                   MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
            break;
        }

        // 发送消息给客户端
        sendto(sockfd, (const char *)server_message, strlen(server_message),
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    }

    // 关闭socket
    close(sockfd);
    printf("Server closed\n");

    return 0;
}
#endif

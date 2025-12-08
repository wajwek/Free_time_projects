#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 8080

void handle_client(int client_fd, int counter) {

    char buf[1024];
    read(client_fd, buf, sizeof(buf));

    FILE *file = fopen("site.html", "rb");
    if (!file) {
        perror("fopen(site.html)");
        close(client_fd);
        return;
    }
    const char *header =
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n";

    if(send(client_fd, header, strlen(header), MSG_NOSIGNAL) <= 0) {
        fclose(file);
        close(client_fd);
        return;
    }

    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), file)) > 0) {
        size_t off = 0;
        while (off < n) {
            ssize_t sent = send(client_fd, buf + off, n - off, MSG_NOSIGNAL);
            if(sent <= 0) {
                fclose(file);
                close(client_fd);
                return;
            }
            off += sent;
        }
    }

    printf("Połączenie nr. %d zakończone\n", counter);
    fclose(file);
    close(client_fd);
}


//=================================MAIN=============================================


int main(void) {
    
    signal(SIGCHLD, SIG_IGN); // Usuwamy procesy zombie, rodzic nie czeka na dziecko

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    int yes = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("Listening on http://localhost:%d/\n", PORT);
    int counter = 1;
    for (;;) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        int child;
        if ((child = fork()) == 0){
            close(server_fd);
            handle_client(client_fd, counter);
            close(client_fd);
            exit(0);
        }
        counter += 1;
    }
    close(server_fd);
    return 0;
}
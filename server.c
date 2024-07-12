#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    //CREATING SOCKET FILE DESCRIPTOR

    if ((server_fd = socket(AF_INET , SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit (EXIT_FAILURE);
    }
    

    //SETTING ADDRESS STRUCTURE

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    //BINDING SOCKET TO ADDRESS
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //LISTENING FOR INCOMING CONNECTIONS

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //ACCEPTING INCOMING CONNECTION

    if ( (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //READING DATA FROM THE CLIENT AND ECHOING IT BACK

    int read_size;
    while ( (read_size = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        write(new_socket, buffer, read_size);}

        if (read_size == -1) {
            perror("read");
        }

        close(new_socket);
        close(server_fd);
        return 0;
    }
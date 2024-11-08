#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 8080
#define BOARD_SIZE 9

int check_win(char board[BOARD_SIZE], char player) {
    if (board[0] == player && board[0] == board[1] && board[1] == board[2]) return 1;
    if (board[3] == player && board[3] == board[4] && board[4] == board[5]) return 1;
    if (board[6] == player && board[6] == board[7] && board[7] == board[8]) return 1;
    if (board[0] == player && board[0] == board[3] && board[3] == board[6]) return 1;
    if (board[1] == player && board[1] == board[4] && board[4] == board[7]) return 1;
    if (board[2] == player && board[2] == board[5] && board[5] == board[8]) return 1;
    if (board[0] == player && board[0] == board[4] && board[4] == board[8]) return 1;
    if (board[2] == player && board[2] == board[4] && board[4] == board[6]) return 1;
    return 0;
}

int check_tie(char board[BOARD_SIZE]) {
    for( int i = 0; i < 9; i++) {
        if(board[i] != 'X' && board[i] != 'O') {
            return 0;
        }
    }
    return 1;
}


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // ...existing code...

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // ...existing code...
    while(1) {
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char board[BOARD_SIZE] = { '1', '2', '3', '4', '5', '6', '7', '8', '9'};

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        } else {
            send(new_socket, board, sizeof(board), 0);
            bool playing = true;
            while(playing) {
                read(new_socket, board, sizeof(board));
                sleep(2);
                if(check_win(board, 'X')) {
                    printf("Player wins!\n");
                    playing = false;
                    break;
                } else if(check_tie(board)) {
                    printf("Tie!\n");
                    playing = false;
                    break;
                } else {
                    bool thinking = true;
                
                    while(thinking) {
                        int random_move = (rand() % 9)+1;
                        if(board[random_move] != 'X' && board[random_move] != 'O') {
                            board[random_move] = 'O';
                            thinking = false;
                        }
                    }
                }
                
                send(new_socket, board, sizeof(board), 0);
                if(check_win(board, 'O')) {
                    printf("Computer wins!\n");
                    playing = false;
                    break;
                }
            }
        }

        close(new_socket);
    }
    
    close(server_fd);
    return 0;
}
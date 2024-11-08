#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "main.h"

#define PORT 8080
#define BOARD_SIZE 9

void display_board(char board[9]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", board[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}

int check_tie(char board[BOARD_SIZE]) {
    for( int i = 0; i < 9; i++) {
        if(board[i] != 'X' && board[i] != 'O') {
            return 0;
        }
    }
    return 1;
}

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

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char board[BOARD_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }



    bool playing = true;
    while(playing) {
        read(sock, board, sizeof(board));
        display_board(board);

        if(check_win(board, 'O')) {
            printf("You lose!\n");
            playing = false;
            break;
        } 

        int move; 
        printf("\nEnter your move: ");
        scanf("%d", &move);

        while(board[move - 1] == 'X' || board[move - 1] == 'O') {
            printf("Invalid move\n");
            printf("Enter your move: ");
            scanf("%d", &move);
            printf("\n");
        }

        board[move - 1] = 'X';

        send(sock, board, sizeof(board), 0);

        if(check_win(board, 'X')) {
            printf("You win!\n");
            playing = false;
        } else if(check_tie(board)) {
            printf("It's a tie!\n");
            playing = false;
        }
    }

    close(sock);
    return 0;
}
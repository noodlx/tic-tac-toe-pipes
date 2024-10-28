#include "parent.h"

void parent(int fd[2], char board[9]) {
    read(fd[0], board, BOARD_SIZE);

    display_board(board);

    int move;
    printf("Player 1: Enter your move: ");
    scanf("%d", &move);
    board[move - 1] = 'X';

    write(fd[1], board, BOARD_SIZE);
}
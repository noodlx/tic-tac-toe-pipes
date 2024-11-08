#include "child.h"

void child(char board[9] ) {
    
    display_board(board);
    int move;
    printf("Player O: Enter your move: \n");
    scanf("%d", &move);
    board[move - 1] = 'O';

}
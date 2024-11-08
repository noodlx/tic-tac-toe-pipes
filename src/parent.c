#include "parent.h"

void parent(char board[9]) {
    
    display_board(board);

    int move;
    printf("Player X: Enter your move: \n");
    scanf("%d", &move);
    board[move - 1] = 'X';



}
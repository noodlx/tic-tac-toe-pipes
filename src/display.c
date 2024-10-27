#include <display.h>

void display_board(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", board[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}
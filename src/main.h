#ifndef MAIN_H
#define MAIN_H

#include "includes.h"
#include "child.h"
#include "parent.h"
#include "display.h"

int main();
int check_win(char board[BOARD_SIZE], char player);
int is_valid_move(char board[BOARD_SIZE], int move);

#endif
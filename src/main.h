#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

int main(int argc, char *argv[]);
int check_win(char board[BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE], int move);
void make_move(char board[BOARD_SIZE], int move, char player);

#endif
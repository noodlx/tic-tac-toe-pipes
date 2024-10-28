#include <main.h>


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

int is_valid_move(char board[BOARD_SIZE], int move) {
    if (move < 1 || move > 9) return 0;
    if (board[move - 1] == 'X' || board[move - 1] == 'O') return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    char board[BOARD_SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    
    int fd[2];

    if(pipe(fd) == -1) {
        perror("Failed to create Pipe...\n");
        return 1;
    } else {
        pid_t pid = fork();

        if(pid == -1) {
            perror("Failed to fork...\n");
            return 1;
        } else if(pid == 0) { // O PLAYER
            while(1) {
                child(fd, board);
                if(check_win(board, 'O')) {
                    display_board(board);
                    printf("Player 2 wins!\n");
                    break;
                } else if(check_win(board, 'X')) {
                    break;
                }
            }
        } else { // X Player
            while(1) {
                parent(fd, board);
                if(check_win(board, 'X')) {
                    display_board(board);
                    printf("Player 1 wins!\n");
                    break;
                } else if(check_win(board, 'O')) {
                    break;
                }
            }
        }
    }
    
    return 0;
}
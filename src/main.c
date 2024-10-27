#include <main.h>


int main(int argc, char *argv[]) {
    char board[BOARD_SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    
    int fd[2];

    if(pipe(fd) == -1) {
        perror("Failed to create Pipe...\n");
        return 1;
    } else {
        pid_t child_pid = fork();

        if(child_pid == -1) {
            perror("Failed to fork...\n");
            return 1;
        } else if(child_pid == 0) {
            child(fd);
        } else {
            parent(fd);
        }
    }
    
    return 0;
}
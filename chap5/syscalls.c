#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


int main() {
    int pipefds[2];
    pipe(pipefds);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(pipefds[1]);
        //dup2(pipefds[0], STDIN_FILENO);
        //close(pipefds[0]);
        //execl("/bin/echo", (char *)NULL);
        char buf[13];
        //lseek(pipefds[0], 0, SEEK_SET);
        //read(pipefds[0], buf, 13);
        //printf("I received message %s\n", buf);
        printf("I am child and pid is %d\n", (int) getpid());
        dup2(pipefds[0], STDIN_FILENO);
        execl("/bin/grep","grep", ".c", (char *)NULL);
        //execl("/bin/ls", ".");
    } else {
        close(pipefds[0]);
        //write(pipefds[1], "hellofromdad\n", 13);
        //close(pipefds[1]);
        dup2(pipefds[1], STDOUT_FILENO);
        execl("/bin/ls", ".");
        //printf("I am the parent and pid is %d\n", (int) getpid());
        wait(NULL);
    }
    return 0;
}

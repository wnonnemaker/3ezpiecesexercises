#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


int main() {
    int fd = open("file.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
    int pipefds[2];
    pipe(pipefds);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char buf[10];
        read(pipefds[0], buf, sizeof(buf));
        execl("/bin/echo", buf);
        printf("I am child and pid is %d\n", (int) getpid());
    } else {
        //volatile unsigned long long i;
        //for (i-0; i < 1ULL << 20; i++);
        //int totallypid = -1;
        //int wrc = wait(&totallypid);
        int subrc = fork();
        if (subrc ==0) {
            printf("I am another child with pid %s", (int) getpid());
            char buf[64] = "hello from the other side!";
            write(pipefds[1], buf, sizeof(buf));
        } else {
            char buf[24] = {0};
            lseek(fd, 0, SEEK_SET);
            read(fd, buf, sizeof(buf));
            //printf("I read :%s from file\n", buf);
            //execl("/bin/ls", ".");
            printf("I am the parent and pid is %d\n", (int) getpid());
        }
    }
    return 0;
}

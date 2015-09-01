#include <sys/wait.h>


int main(int argc, char *argv[])
{
    int status;
    pid_t childPid;
    childPid = fork();

    if(childPid == -1)
        exit(-1);
    else if(childPid == 0)
    {
        printf("Child started with PID = %ld\n", (long) getpid());
        while(1)
            pause();


    }
    else
    {
        while(1) {
            childPid = waitpid(-1, &status, WUNTRACED|WCONTINUED);
            if (childPid == -1)
                exit(-1);



            printf("waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n",(long) childPid,(unsigned int) status, status >> 8, status & 0xff);

            if (WIFEXITED(status) || WIFSIGNALED(status))
                exit(0);
        }
    }
}

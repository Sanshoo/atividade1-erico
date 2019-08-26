#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */


        
int main(void)
{
char *args[MAX_LINE/2 + 1]; /* command line arguments */
int should_run = 1; /* flag to determine when to exit program */
while (should_run) {
printf("osh>");
fflush(stdout);
}
/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) parent will invoke wait() unless command included &
*/
return 0;
}


/* forking a child process
{
pid_t pid;

       // fork a child process 
       pid = fork();
       
       if (pid < 0) { // error occurred 
        fprintf(stderr, "Fork Failed");
        return 1;
        }
        else if (pid == 0) { // child process 
        execlp("/bin/ls","ls", NULL);
        }
        else { //parent process 
        //parent will wait for the child to complete 
        wait(NULL);
        printf("Child Complete");
        }
        
        return 0;
        
        }
        */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_LINE 80 

char *getString()
{
    fflush(stdout);
    int string_pos = 0;
    int length = 1;
    char *text = (char *)malloc(length*sizeof(char));
    char c;
    while(1) {
        c = getchar();
        if(c == '\n') {
            break;
        }
        length++;
        text = (char *)realloc(text,length*sizeof(char));
        text[string_pos] = c;
        string_pos++;
    }
    return text;
}

int length(char *text){
    int result = strlen(text);
    return result;
}

int compareStrings(char *text1, char *text2){
    int result = FALSE;
    int primarylength = length(text1);
    if(primarylength == length(text2)){
        for(int i = 0; i < primarylength;i++){
            if(text1[i] != text2[i]){
                break;
            }
            else if(i == primarylength - 1){
                result = TRUE;
            }
        }
    }
    return result;
}



char commandGetter(){
    while(TRUE){

        printf("GiveTheIdea>");
        char *command = getString();
        char quit [6] = "quit()"; 
        if (compareStrings(command,quit)){
            printf("\nQuitting..");
            free(command);
            break;
        }
        pid_t pid;
        pid = fork();

        if(pid < 0) {
            fprintf(stderr,"fork failed");
        }
        else if(pid == 0 && compareStrings(command,"ls")) {
            execlp("/bin/ls","ls",NULL);
        }
        else if(pid == 0){
            execvp(*command,command);
        }
        else {
            wait(NULL);
            // printf("child completed");
        }   
        free(command);
    }
}

int main(void)
{
    system("echo 'HELLO'");
    commandGetter();

}

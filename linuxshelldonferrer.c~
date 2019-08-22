#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX_LINE 80 

struct args {
    char *content;
    struct args *next;
}args;


void showHist(char *hist[],int args_counter){
    if(args_counter == 0){
        printf("\nNo commands in history!");
    }
    else {
        for(int i = 0;i < args_counter;i++){
            int j = 0;
            while(hist[i][j] != '\n' || hist[i][j] != '0' || hist[i][j] != '\0'){
                printf("%c",hist[i][j]);
                j++;
            }
            printf('\n');
        }
    }
}

char *getString()
{
    fflush(stdout);
    int string_pos = 0;// Setting the current position of the char;
    int length = 1;// Setting the initial length of the String
    char *text = (char *)malloc(length*sizeof(char));// Allocating the main pointer of chars size
    char c;// Current char
    while(1) {
        c = getchar();// getting char input
        if(c == '\n') {
            break;
        }
        // if(c == ' ') c = '0';
        length++;// Adding length
        text = (char *)realloc(text,length*sizeof(char));// Realloching pointer size
        text[string_pos] = c;// Pushing current char into the String
        string_pos++;// Setting the new char position
    }
    return text;//Returning String
}

int length(char *text){ //  Just a abstraction ignore that
    int result = strlen(text);
    return result;
}

int compareStrings(char *text1, char *text2){ // Function to compare strings
    int result = FALSE; // Initial result
    int primarylength = length(text1); // getting the 1st length
    if(primarylength == length(text2)){ // Comparing the 1st length to the 2nd one
        for(int i = 0; i < primarylength;i++){ 
            if(text1[i] != text2[i]){
                break;
            }
            else if(i == primarylength - 1){
                result = TRUE; // If the comparison ends with the length, the results turns true
            }
        }
    }
    return result;
}

char *getCommandType(char *command){
    int len = length(command);

    for(int i = 0;i < len;i++){
        if(command[i] == ' ' || (i == len-1 && command[i+1] == '\n')){
            char *type = malloc(sizeof(char)*i+1);
            strncpy(type,command,i);
            return type;
        }
        
    }
    return NULL;
}

// char *getCommandArguments(char *command){a
//     char *
// }

char commandGetter(){
    char *args[MAX_LINE/2+1];
    int args_counter = 0;
    char args_hist[12][MAX_LINE];

    while(TRUE){

        printf("osh>");
        char *command = getString();
        args_counter++;
        char *commandtype = getCommandType(command);

        // strcpy(command,args[args_counter]);
        strcpy(args_hist[args_counter],command);

        char quit [6] = "quit()"; 
        if (compareStrings(command,quit)){
            printf("\nQuitting..");
            free(command);
            free(commandtype);
            return 0;
        }

        pid_t pid;
        pid = fork();

        if (compareStrings(command,"history")){
            showHist(args_hist, args_counter);
        }
        
        // printf("%s",command);
        // printf("%s",commandtype);
        // printf("%s",args_hist[0]);


        if(pid < 0) {
            fprintf(stderr,"fork failed");
        }
        else if(pid == 0) {
            if(compareStrings(command,"ls")){
                execlp("/bin/ls","ls",NULL);
            }
        }
        // else if(pid == 0){
        //     execvp(command,command);
        // }
        else {
            wait(NULL);
            // printf("child completed");
        }   
        // free(command);
        free(commandtype);
    }
}

int main(void)
{
    system("echo 'HELLO'");
    commandGetter();

}

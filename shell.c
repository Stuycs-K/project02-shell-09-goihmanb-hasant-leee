#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("hello world\n");

    return 0;
}


void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}

void redirect_output(char * fileName, char * output) {
  //going from file into standard output?
  int fd1 = open(fileName, O_WRONLY); //opens a file for storing output
  // if file doesn't exist, make one? Or maybe that should be in main
  int FILENO = stdout; //stores standard output
  int backup_stdout = dup(FILENO); //also stores standard output
  dup2(fd1, FILENO); //redirects the file content to standard output
  //write(fd1, &FILENO, sizeof(int));
}

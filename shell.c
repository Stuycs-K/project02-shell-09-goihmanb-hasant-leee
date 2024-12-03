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


void redirectOut(){
  int fd1 = open("foo.txt", O_WRONLY);
  int FILENO = stdout;
  int backup_stdout = dup( FILENO ) // save stdout for later
  dup2(fd1, FILENO);
  printf("TO THE FILE!!!\n");
  fflush(stdout);//not needed when a child process exits, becaue exiting a process will flush automatically.
  dup2(backup_stdout, FILENO)
}

void redirectIn(){

}

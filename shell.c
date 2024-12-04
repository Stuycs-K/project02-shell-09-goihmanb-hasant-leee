#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>




void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}


void redirect_in(char * fileName){
  //changing the input to be a file instead of stdin
  int fd1 = open("foo.txt", O_WRONLY);
  int FILENO = stdin;
  int backup_stdout = dup( FILENO ) // save stdin for later
  dup2(fd1, FILENO);
  fflush(stdout);
  dup2(backup_stdout, FILENO);

}


int main(int argc, char *argv[]){
    printf("hello world\n");
    redirect_in("tempIn.txt", "myinput");
    return 0;
}

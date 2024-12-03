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


void redirect_in(char * fileName, char * input){
  //changing the input to be a file instead of stdin
  int w_file = open(fileName,
      O_WRONLY | O_APPEND | O_CREAT, 0611);
  if(w_file==-1)err();
  printf("w_file: %u\n",w_file);
  int n = strlen(input)/4;
  write( w_file, input, n);
}


int main(int argc, char *argv[]){
    printf("hello world\n");
    redirect_in("tempIn.txt", "myinput");
    return 0;
}

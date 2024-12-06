#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>


int errorMessage() {
    printf("errno %d\n", errno);
    printf("%s\n", strerror(errno));
    return 1;
}

void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}

void redirect_output(char * fileName) { //I need to make it so that it creates a file in the project directory
  //going from file into standard output?
  char * path = "/home/thasan50/p02-sys/"; //Could it be that the problem is from it being a pointer instead of an array?
  strcat(path, fileName);
  int fd1 = open(path, O_WRONLY | O_APPEND | O_CREAT, 0611); //opens a file for storing output
  if (fd1 == -1) {
    errorMessage();
  }
  int FILENO = 1; //stores standard output
  int backup_stdout = dup(FILENO); //also stores standard output
  dup2(fd1, FILENO); //redirects the standard output to file
  //printf("Print");
}

void get_cmds(char** cmds){
    //Parses all commands in-memory broken by semicolon using strsep
    char line_buff[1000];
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s$", cwd);
    }
    if (fgets(line_buff, sizeof(line_buff), stdin) == NULL) {
      exit(1);
    }
    line_buff[strcspn(line_buff, "\n")] = 0; //Removes newline breaks code
    char *curr = line_buff;
    char * token;
    token = strsep( &curr, ";" );
    int i = 0;
    while(token){
        cmds[i] = malloc(strlen(token) + 1);
        strcpy(cmds[i],token);
        token = strsep( &curr, ";" );
        i++;
    }
    //printf(line_buff);
}

void execute_cmds(char** cmds, char * path){
    //Executes all commands in cmds array
    int i = 0;
    while (cmds[i]){
        char *arg_ary[1000];
        parse_args(cmds[i], arg_ary);
        if (strcmp(arg_ary[0], "cd") == 0){
            chdir(arg_ary[1]);
            i++;
            printf("Changed directory to %s\n", arg_ary[1]);
        }
        else{
          int pid = fork();
          if (pid == 0){
              redirect_output(path);
              execvp(arg_ary[0], arg_ary);
          }
          else{
              wait(NULL);
              printf("Executed command %s\n", cmds[i]);
          }
          i++;
      }
    }
}
void redirect_in(char * fileName){
  //changing the input to be a file instead of stdin
  int fd1 = open("foo.txt", O_WRONLY);
  int FILENO = stdin;
  int backup_stdout = dup( FILENO ); // save stdin for later
  dup2(fd1, FILENO);
  fflush(stdout);
  dup2(backup_stdout, FILENO);

}

int main(int argc, char *argv[]) {
    char **cmds = (char **) malloc(sizeof(char*)*1000);
    char projectDir[500];
    char path[1000];
    if (getcwd(projectDir, sizeof(projectDir)) == NULL) {
        errorMessage();
    }
    snprintf(path, sizeof(path), "%s/%s", projectDir, "foo.txt");
    while (1) {
      get_cmds(cmds);
      // char *home = getenv("HOME");
      // chdir(home);
      execute_cmds(cmds, path);
    }

    return 0;
}

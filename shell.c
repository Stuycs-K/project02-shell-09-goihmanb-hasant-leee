#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>



void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}

void redirect_output(char * fileName, char * output) {
  //going from file into standard output?
  int fd1 = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0611); //opens a file for storing output
  // if file doesn't exist, make one? Or maybe that should be in main
  int FILENO = stdout; //stores standard output
  int backup_stdout = dup(FILENO); //also stores standard output
  dup2(FILENO, fd1); //redirects the standard output to file
}
void redirect_output2(char * fileName, char * output) {
    int fd2 = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0611); //opens a file for storing output
  // if file doesn't exist, make one? Or maybe that should be in main
  int FILENO = stdout; //stores standard output
  int backup_stdout = dup(FILENO); //also stores standard output
  dup2(fd2, FILENO); //redirects the file to standard output
}
void get_cmds(char** cmds){
    //Parses all commands in-memory broken by semicolon using strsep
    char line_buff[1000];
    printf("enter command: ");
    fgets(line_buff, sizeof(line_buff), stdin);
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
}

void execute_cmds(char** cmds){
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

int main(int argc, char *argv[]) {
    char **cmds = (char **) malloc(sizeof(char*)*1000);
    get_cmds(cmds);
    char *home = getenv("HOME");
    chdir(home);
    execute_cmds(cmds);
    return 0;
}

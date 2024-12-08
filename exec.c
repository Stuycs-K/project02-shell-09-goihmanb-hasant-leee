#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}
void redirect_output(char * fileName) {
  //sets stdout to be a file instead of stdout
  int fd1 = open(fileName, O_WRONLY | O_TRUNC | O_CREAT, 0611); //opens a file for storing output
  // if file doesn't exist, make one? Or maybe that should be in main
  int FILENO = 1; //stores standard output
  int backup_stdout = dup(FILENO); //also stores standard output
  dup2(fd1, FILENO); //redirects the standard output to file
}

void redirect_in(char * fileName){
  //changing the input to be a file instead of stdin
  int fd1 = open(fileName, O_RDONLY);
  int FILENO = 0;
  int backup_stdout = dup( FILENO ); // save stdin for later
  dup2(fd1, FILENO);
  close(fd1);
}

int check_for_redir(char* arg_ary[]){
    int i = 0;
    while (arg_ary[i]){
        if (strcmp(">",arg_ary[i])==0){
            return i;
        }
        i++;
    }
    return -1;
}

int check_for_redir_in(char* arg_ary[]){
    int i = 0;
    while (arg_ary[i]){
        if (strcmp("<",arg_ary[i])==0){
            return i;
        }
        i++;
    }
    return -1;
}

void run_cmd_pipe(char * cmd1, char * cmd2){
    FILE *fp1, *fp2;
    char buffer[10000];

    fp1 = popen(cmd1, "r");
    if (fp1 == NULL) {
        perror("popen failed");
        return;
    }

    fp2 = popen(cmd2, "w");
    if (fp2 == NULL) {
        perror("popen failed");
        pclose(fp1);
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp1) != NULL) {
        fprintf(fp2, "%s", buffer);
    }

    pclose(fp1);
    pclose(fp2);
}

int check_for_pipe(char* arg_ary[]){
    int i = 0;
    while (arg_ary[i]){
        if (strcmp("|", arg_ary[i]) == 0){
            return i;
        }
        i++;
    }
    return -1;
}
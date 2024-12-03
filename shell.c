#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>




void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}

void get_cmds(char** cmds){
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

int main(int argc, char *argv[]) {
    char **cmds = (char **) malloc(sizeof(char*)*1000);
    get_cmds(cmds);
    int i = 0;
    while (cmds[i]){
        printf("%s\n",cmds[i]);
        i++;
    }
    char *home = getenv("HOME");
    printf("Home: %s\n", home);
    chdir(home);
    char *arg_ary[1000];
    parse_args(cmds[0], arg_ary);
    printf("arg_ary[0]: %s\n", arg_ary[0]);
    printf("arg_ary[1]: %s\n", arg_ary[1]);
    int pid = fork();
    if (pid == 0){
        execvp(arg_ary[0], arg_ary);
    }
    else{
        wait(NULL);
    }

    return 0;
}
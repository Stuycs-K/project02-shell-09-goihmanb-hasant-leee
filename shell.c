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
    printf("%s\n",cmds[0]);
    printf("%s",cmds[1]);
    return 0;
}
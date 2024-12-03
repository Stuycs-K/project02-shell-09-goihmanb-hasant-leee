#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char cmds[argc/2][1000];
    int j = 0;
    cmds[0][0] = 0;
    char line_buff[1000];
    printf("enter command: ");
    fgets(line_buff, sizeof(line_buff), stdin);
    char *curr = line_buff;
    char * token;
    token = strsep( &curr, ";" );
    int i = 0;
    while(token){
        strcpy(cmds[i],token);
        token = strsep( &curr, ";" );
        i++;
    }
        printf("%s\n",cmds[0]);
        printf("%s\n",cmds[1]);

    return 0;
}


void parse_args(char* line, char ** arg_ary){
    //Parses single command in-memory
    int i = 0;
    while((arg_ary[i] = strsep( &line, " " ))){ i++;}
}

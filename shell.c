#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "exec.h"





void get_cmds(char** cmds){
    //Parses all commands in-memory broken by semicolon using strsep
    char line_buff[1000];
    char path[500];
    getcwd(path, sizeof(path));
    if (strncmp(path, getenv("HOME"), strlen(getenv("HOME"))) == 0) {
      printf("~%s$", path+strlen(getenv("HOME")));
    }
    else {
      printf("%s$", path);
    }

    if (fgets(line_buff, sizeof(line_buff), stdin) == NULL) {
      printf("\n");
      exit(0);
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
}



void execute_cmds(char** cmds){
    int i = 0;
    while (cmds[i]){
        char *arg_ary[1000];
        parse_args(cmds[i], arg_ary);
        if (strcmp(arg_ary[0], "cd") == 0){
          if (arg_ary[1] == NULL) {
            chdir(getenv("HOME"));
            i++;
          }
          else {
            chdir(arg_ary[1]);
            i++;
          }

        }
        else if (strcmp(arg_ary[0],"exit")==0){
            exit(0);
        }
        else if (check_for_pipe(arg_ary) != -1){
            printf("Executing pipe command %s\n", cmds[i]);
            int pipe_idx = check_for_pipe(arg_ary);
            char cmd1[10000] = "";
            char cmd2[10000] = "";
            
            for (int j = 0; j < pipe_idx; j++) {
                strcat(cmd1, arg_ary[j]);
                strcat(cmd1, " ");
            }
            
            int iannoyedme = pipe_idx + 1; //BRUHHHHHHHH I WAS INCREMENTING THIS I not the counter ):::::::
            while(arg_ary[iannoyedme]) {
                strcat(cmd2, arg_ary[iannoyedme]);
                strcat(cmd2, " ");
                iannoyedme++;
            }

            
            run_cmd_pipe(cmd1, cmd2);
            i++;
        }
        else{
        printf("Executing command %s\n", cmds[i]);
        int pid = fork();
        if (pid == 0){
            int idx = check_for_redir(arg_ary);
            if(idx!=-1){
                redirect_output(arg_ary[idx+1]);
                char *out_ary[1000];
                for (int i = 0; i < idx;i++){
                    out_ary[i]=arg_ary[i];
                }
                out_ary[idx]=NULL;
                execvp(out_ary[0], out_ary);
            }
            int idx2 = check_for_redir_in(arg_ary);
            if(idx2!=-1){
                redirect_in(arg_ary[idx2+1]);
                char *in_ary[1000];
                for (int i = 0; i < idx2;i++){
                    in_ary[i]=arg_ary[i];
                }
                in_ary[idx2]=NULL;
                execvp(in_ary[0], in_ary);
            }
            execvp(arg_ary[0],arg_ary);
        }
        else{
            wait(NULL);
            //     int pid = fork();
            //     if (pid == 0){
            //     redirect_output("foo.txt");
            //     execvp(arg_ary[0],arg_ary);
            //  }
            printf("Executed command %s\n", cmds[i]);
        }
        i++;
    }
    }}




int main(int argc, char *argv[]) {
    char **cmds = (char **) malloc(sizeof(char*)*1000);
    // get_cmds(cmds);
    // execute_cmds(cmds);
    while (1) {
      get_cmds(cmds);
      execute_cmds(cmds);
    }

    return 0;
}

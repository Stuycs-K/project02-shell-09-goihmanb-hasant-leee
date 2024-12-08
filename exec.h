#ifndef EXEC_H
#define EXEC_H

void parse_args(char* line, char ** arg_ary);
void redirect_output(char * fileName);
void redirect_in(char * fileName);
int check_for_redir(char* arg_ary[]);
int check_for_redir_in(char* arg_ary[]);
void run_cmd_pipe(char * cmd1, char * cmd2);
int check_for_pipe(char* arg_ary[]);

#endif

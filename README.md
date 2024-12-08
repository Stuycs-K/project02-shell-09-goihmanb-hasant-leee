[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell
## Team Name:
- Benjamin Goihman
- Tanzeem Hasan
- Ethan Lee
## Creative name
The Porpoises 
## Shell features implemented
- Run commands
- Loop of user input
- Exit with ctrl-d and exit command
- Redirect input
- Redirect output
- Pipe commands
- Multiple commands with semicolon separation
## Shell features tried but failed
- N/A
## bugs
- N/A
## headers
- int main(int argc, char *argv[])
- void parse_args(char* line, char ** arg_ary)
- void redirect_output(char * fileName)
- void get_cmds(char** cmds)
- int check_for_redir(char* arg_ary[])
- int check_for_redir_in(char* arg_ary[])
- void run_cmd_pipe(char * cmd1, char * cmd2)
- int check_for_pipe(char* arg_ary[])
- void redirect_in(char * fileName)
- void execute_cmds(char** cmds)

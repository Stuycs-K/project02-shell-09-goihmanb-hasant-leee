.PHONY: compile clean


compile: shell.o exec.o
	@gcc -o shell shell.o exec.o -lm

shell.o: shell.c exec.h
	@gcc -c shell.c

exec.o: exec.c exec.h
	@gcc -c exec.c

clean:
	@rm -f *.o
	@rm -f shell
	@rm -f *.txt
	@rm -f *.out


.PHONY: compile clean
compile shell: shell.o
	@gcc -o shell shell.o -lm
shell.o: shell.c
	@gcc -c shell.c -lm
clean:
	@rm -f *.o
	@rm -f shell
	@rm -f *.txt
	@rm -f *.out
	

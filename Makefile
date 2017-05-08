all:
	@gcc -o rff src/rff.c src/filestrings.c -I./include -g -Wall -lm
run:
	@./rff
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./rff

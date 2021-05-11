all:
	gcc -c *.c
	gcc -o programaTrab *.o -Wall -Werror -g -lm
	rm *.o

run:
	./programaTrab

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all -v ./main
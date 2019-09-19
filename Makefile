build:
	gcc -Wall -Werror widget.c -o widget

test:
	make
	./widget -l stateless
	./widget -f stateful

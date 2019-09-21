build:
	gcc -Wall -Werror widget.c -o widget

test:
	make
	./widget -l stateless
	./widget -f stateful
	./widget -l example/stateless
	./widget -f example/stateful

clean:
	rm *.dart
	rm example/*.dart

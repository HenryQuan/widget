build:
	gcc -Wall -Werror widget.c -o widget

test:
	make
	./widget -l stateless
	./widget -f stateful
	./widget -f testButton
	./widget -f FancyClass
	./widget -f AmazingComponent
	./widget -l example/stateless
	./widget -f example/stateful
	./widget -f example/testButton
	./widget -f example/FancyClass
	./widget -f example/AmazingComponent

clean:
	rm *.dart
	rm widget
	rm example/*.dart

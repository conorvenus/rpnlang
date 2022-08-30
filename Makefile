run: build
	./build/main.exe $(ARGS)

build: src/main.c src/lexer.c src/char.c
	if not exist build mkdir build
	gcc src/main.c src/lexer.c src/char.c -o build/main.exe

clean: build
	rd /s /q build
CCompiler = gcc
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c23 -fsanitize=address -flto -fstack-protector-strong -I./include

main: main.o
	$(CCompiler) $(CFlags) $< -o $@

clean:
	clear; rm -rfv *.o; rm -fv main

%.o: %.c
	$(CCompiler) $(CFlags) -c $< -o $@


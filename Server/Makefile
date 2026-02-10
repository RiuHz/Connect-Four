CCompiler = gcc
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O3 -std=c17 -fsanitize=address -flto -fstack-protector-strong -I./include

main: main.o
	$(CCompiler) $(CFlags) $< -o $@

clean:
	clear; rm -rfv *.o; rm -fv main

%.o: %.c
	$(CCompiler) $(CFlags) -c $< -o $@


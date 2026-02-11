CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong -I./include

main: main.o core/setup/setup.o core/board/board.o
	$(CCompiler) $(CFlags) $^ -o $@

clean:
	clear; rm -rfv *.o; rm -fv main

%.o: %.cpp
	$(CCompiler) $(CFlags) -c $< -o $@

main.o: main.cpp

setup.o: core/setup/setup.cpp

board.o: core/board/board.hpp

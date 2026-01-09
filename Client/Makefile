CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong -I./include

main: main.o
	$(CCompiler) $(CFlags) $< -o $@

clean:
	clear; rm -rfv *.o; rm -fv main

%.o: %.cpp
	$(CCompiler) $(CFlags) -c $< -o $@

main.o: main.cpp enum/TextColors.hpp enum/TextStyles.hpp

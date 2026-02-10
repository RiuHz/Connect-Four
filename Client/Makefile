CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong -I. -I./include

main: main.o UDPClient.o
	$(CCompiler) $(CFlags) $^ -o $@

clean:
	clear; rm -rfv *.o; rm -fv main

main.o: main.cpp enum/TextColors.hpp enum/TextStyles.hpp headers/UDPClient.hpp
	$(CCompiler) $(CFlags) -c main.cpp -o main.o


UDPClient.o: classes/UDPClient.cpp headers/UDPClient.hpp
	$(CCompiler) $(CFlags) -c classes/UDPClient.cpp -o UDPClient.o
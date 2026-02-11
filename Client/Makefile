CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong

main: main.o core/setup/setup.o core/board/board.o core/network/UDPClient.o
	$(CCompiler) $(CFlags) $^ -o $@

debug: main.o core/setup/setup.o core/board/board.o core/network/UDPClient.o
	$(CCompiler) $(CDebugFlags) $^ -o $@

clean:
	clear; rm -rfv *.o; rm -fv main debug

main.o: main.cpp

setup.o: core/setup/setup.cpp

board.o: core/board/board.cpp

UDPClient.o: core/network/UDPClient.cpp

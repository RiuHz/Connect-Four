CCompiler = gcc
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c23 -fsanitize=address -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O3 -std=c17 -fsanitize=address -flto -fstack-protector-strong

main: main.o core/network/UDPServer.o
	$(CCompiler) $(CFlags) $< -o $@

debug: main.o core/network/UDPServer.o
	$(CCompiler) $(CDebugFlags) $^ -o $@

clean:
	clear; rm -rfv *.o; rm -fv main debug

%.o: %.c
	$(CCompiler) $(CDebugFlags) -c $< -o $@


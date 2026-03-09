CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O0 -std=c++23 -fsanitize=address -fstack-protector-strong
CTestFlags = -Wconversion -Wall -Wextra -pedantic -g -fno-omit-frame-pointer -O0 -std=c++23 -fsanitize=address -fstack-protector-strong

SRC = main.cpp \
	core/board/GameBoard.cpp \
	core/client/Client.cpp \
	core/window/Window.cpp \
	model/message/Message.cpp \
	network/tcp/TCPClient.cpp

OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CCompiler) $(CFlags) $^ -o $@ -lncurses

debug: CFlags := $(CDebugFlags)
debug: $(OBJ)
	$(CCompiler) $(CDebugFlags) $^ -o $@ -lncurses

test: CFlags := $(CTestFlags)
test: $(OBJ)
	$(CCompiler) $(CTestFlags) $^ -o $@ -lncurses

clean:
	clear; rm -rfv $(OBJ); rm -fv main debug

%.o: %.cpp
	$(CCompiler) $(CFlags) -c $< -o $@

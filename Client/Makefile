CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O0 -std=c++23 -fsanitize=address -fstack-protector-strong

SRC = main.cpp \
	network/tcp/TCPClient.cpp \
	core/state/context/ClientContext.cpp \
	core/state/login/LoginState.cpp \
	core/state/menu/MenuState.cpp \
	core/state/partita/PartitaState.cpp \
	core/state/lista/ListaPartiteState.cpp \
	network/packet/PacketBuilder.cpp
OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CCompiler) $(CFlags) $^ -o $@

debug: CFlags := $(CDebugFlags)
debug: $(OBJ)
	$(CCompiler) $(CDebugFlags) $^ -o $@

clean:
	clear; rm -rfv $(OBJ); rm -fv main debug

%.o: %.cpp
	$(CCompiler) $(CFlags) -c $< -o $@

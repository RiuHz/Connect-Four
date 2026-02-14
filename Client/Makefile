CCompiler = g++
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O3 -std=c++23 -fsanitize=address -flto -fstack-protector-strong

SRC = main.cpp \
	core/setup/setup.cpp core/network/UDPClient.cpp 

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

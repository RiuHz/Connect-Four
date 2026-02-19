CCompiler = gcc
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c23 -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O3 -std=c17 -fsanitize=address -flto -fstack-protector-strong

SRC = main.c

OBJ = $(SRC:.c=.o)

main: $(OBJ)
	$(CCompiler) $(CFlags) $< -o $@

debug: CFlags := $(CDebugFlags)
debug: $(OBJ)
	$(CCompiler) $(CDebugFlags) $^ -o $@

clean:
	clear; rm -rfv $(OBJ); rm -fv main debug

%.o: %.c
	$(CCompiler) $(CFlags) -c $< -o $@


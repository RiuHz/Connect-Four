CCompiler = gcc
CFlags = -Wconversion -Wall -Wextra -Werror -pedantic -O3 -std=c23 -flto -fstack-protector-strong
CDebugFlags = -Wconversion -Wall -Wextra -Werror -pedantic -g -fno-omit-frame-pointer -O3 -std=c17 -fsanitize=address -flto -fstack-protector-strong

SRC = main.c \
	core/controller/client/client.c \
	core/handler/event/events.c \
	core/handler/request/requests.c \
	core/handler/response/responses.c \
	core/threading/broadcast/broadcast.c \
	core/threading/client/client.c \
	data/client/client.c \
	data/coda/coda.c \
	data/lista/lista.c \
	data/partita/partita.c \
	data/server/server.c \
	network/messaggio/messaggio.c \
	network/tcp/broadcast/TCPBroadcast.c \
	network/tcp/core/TCPServer.c

OBJ = $(SRC:.c=.o)

main: $(OBJ)
	$(CCompiler) $(CFlags) $^ -o $@

debug: CFlags := $(CDebugFlags)
debug: $(OBJ)
	$(CCompiler) $(CDebugFlags) $^ -o $@

clean:
	clear; rm -rfv $(OBJ); rm -fv main debug

%.o: %.c
	$(CCompiler) $(CFlags) -c $< -o $@

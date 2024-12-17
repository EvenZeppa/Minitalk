CC = gcc
C_FLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude
LIBS = libft.a
SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_TARGET = server
CLIENT_TARGET = client

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET):
	$(CC) $(C_FLAGS) $(INCLUDES) $(SERVER_SRC) $(LIBS) -o $(SERVER_TARGET)

$(CLIENT_TARGET):
	$(CC) $(C_FLAGS) $(INCLUDES) $(CLIENT_SRC) $(LIBS) -o $(CLIENT_TARGET)

clean:
	rm -f $(SERVER_TARGET)
	rm -f $(CLIENT_TARGET)

re: clean all
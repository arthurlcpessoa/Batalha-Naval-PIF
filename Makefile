# Makefile para Batalha Naval

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC_DIR = src
OBJ_DIR = obj
TARGET = batalha_naval

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Regra padrão

all: $(TARGET)

# Compilação do executável

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos objetos

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria a pasta obj se não existir

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos compilados

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)


###
# AUTORES: EDUARDO OLIVEIRA & CARLOS MIRANDA, VERSÃO: V 1.0
# DATA: 06/03/2020

### Definição e utilização de flags do compilador
# -Wall Warnings do compilador
# Para C definir CC = gcc

# Modo de compilação para C - gcc
CC = gcc

# Flags para compilação. Por norma as flags necessárias para compilar um programa base já estão definidas em linux
CFLAGS := -Wall -g

# Flags para pré-processador
CPPFLAGS := -Iinclude

# Nome do projeto
EXE := Interrail

# Diretórios - objetcs & source
SRC_DIR := src
OBJ_DIR := obj

# Listar todas as fontes
SRC = $(wildcard $(SRC_DIR)/*.c)

# Listar todos os objetos, a partir das fontes
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Comando rm para linux
RM := rm

# Regra especial: Indicar quando uma regra não produz output
.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $^ -lm -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJ)
	rmdir $(OBJ_DIR)
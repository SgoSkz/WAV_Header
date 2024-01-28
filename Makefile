SRC		= ./src

all: WAV_Header

WAV_Header: ${SRC}/main.c
	gcc ${INCLUDE} ${SRC}/main.c -o WAV_Header

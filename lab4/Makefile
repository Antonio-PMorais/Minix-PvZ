# name of the program (Minix service)
PROG = lab4

# Labs
LAB1_DIR = ../lab1
LAB2_DIR = ../lab2
LAB3_DIR = ../lab3

# source code files to be compiled
SRCS = lab4.c mouse.c ${LAB2_DIR}/timer.c ${LAB2_DIR}/utils.c ${LAB3_DIR}/keyboard.c

.BEGIN:
	${MAKE} -C ${LAB3_DIR}

# additional compilation flags
CFLAGS += -pedantic
CFLAGS += -DLAB4

LIB_NAME = libmouse.a
LIB_SRCS = mouse.c ${LAB2_DIR}/utils.c ${LAB2_DIR}/timer.c ${LAB3_DIR}/keyboard.c
LIB_OBJS = ${notdir ${LIB_SRCS:.c=.o}}

# Dependencies and Linker flags
DPADD += ${LIBLCF} ${LIB_NAME} ${LAB2_DIR}/libtimer.a ${LAB3_DIR}/libkeyboard.a
LDADD += -llcf -L. -lmouse -L${LAB2_DIR} -ltimer -L${LAB3_DIR} -lkeyboard

# Files to remove on 'make clean'
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

# Tell make to build the local library before the program
all: lib
lib: ${LAB2_DIR}/libtimer.a ${LAB3_DIR}/libkeyboard.a ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Explicit rules to ensure .o files are generated for the library
mouse.o: mouse.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c mouse.c -o mouse.o

utils.o: ${LAB2_DIR}/utils.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c ${LAB2_DIR}/utils.c -o utils.o

timer.o: ${LAB2_DIR}/timer.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c ${LAB2_DIR}/timer.c -o timer.o

keyboard.o: ${LAB3_DIR}/keyboard.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c ${LAB3_DIR}/keyboard.c -o keyboard.o

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
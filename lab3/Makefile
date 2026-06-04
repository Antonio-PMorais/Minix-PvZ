# name of the program (Minix service)
PROG=lab3 

# source code files to be compiled
SRCS = lab3.c keyboard.c

# additional compilation flags
CFLAGS += -pedantic
CFLAGS += -DLAB3

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}

LAB1_DIR = ../lab1
LAB2_DIR = ../lab2
.BEGIN:
	${MAKE} -C ${LAB2_DIR}
    
LDADD += -L${LAB2_DIR} -ltimer 

LIB_NAME = libkeyboard.a
LIB_SRCS = keyboard.c ../lab2/utils.c
LIB_OBJS = ${LIB_SRCS:.c=.o}

# Dependencies and Linker flags
DPADD += ${LIBLCF} ${LIB_NAME}
LDADD += -llcf -L. -lkeyboard

# Files to remove on 'make clean'
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

# Tell make to build the local library before the program
all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Explicit rules to ensure .o files are generated for the library
keyboard.o: keyboard.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c keyboard.c -o keyboard.o

../lab2/utils.o: ../lab2/utils.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c ../lab2/utils.c -o ../lab2/utils.o
    
${LAB2_DIR}/libtimer.a:
	${MAKE} -C ${LAB2_DIR}

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
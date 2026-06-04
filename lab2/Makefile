# name of the program (Minix service)
PROG=lab2 

LAB1_DIR = ../lab1

# source code files to be compiled
SRCS = lab2.c timer.c utils.c

.BEGIN:
	${MAKE} -C ${LAB1_DIR}

# additional compilation flags
CFLAGS += -pedantic

DPADD += ${LIBLCF} ${LIB_NAME}
LDADD += -llcf -L. -ltimer

LIB_NAME = libtimer.a
LIB_SRCS = timer.c utils.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Explicit rules to ensure .o files are generated for the library
timer.o: timer.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c timer.c -o timer.o

utils.o: utils.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c utils.c -o utils.o

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
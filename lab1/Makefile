PROG = lab1 
SRCS = main.c rtc.c bitwise.c

CFLAGS += -pedantic

DPADD += ${LIBLCF}
LDADD += -llcf

# Library generation settings
LIB_NAME = librtc.a
LIB_SRCS = rtc.c bitwise.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME}

all: ${PROG} lib

lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Explicit rules for the object files
rtc.o: rtc.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c rtc.c -o rtc.o

bitwise.o: bitwise.c
	${CC} ${CFLAGS} ${CPPFLAGS} -c bitwise.c -o bitwise.o

.include <minix.lcom.mk>
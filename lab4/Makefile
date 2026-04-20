# name of the program (Minix service)
PROG=lab4

# source code files to be compiled
SRCS = lab4.c mouse.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -DLAB4 -I../lab2 -I..

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf
LDADD += -llcf -L../lab2  # Tell the compiler to look in the lab2 directory for libraries
LDADD += -ltimer          # Link the library named libtimers.a

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>

LDADD += -llcf -L../lab2  # Tell the compiler to look in the lab2 directory for libraries
LDADD += -ltimer          # Link the library named libtimers.a

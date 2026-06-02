# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = proj.c timer.c keyboard.c mouse.c rtc.c v_card.c utils.c game.c menu.c font.c entities.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CPPFLAGS += -pedantic -D__LCOM_OPTIMIZED__
CPPFLAGS += -DLEVEL_PATH=\"/home/lcom/labs/grupo_2leic13_5/proj/levels\"

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
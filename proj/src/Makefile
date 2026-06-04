# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/drivers
.PATH: ${.CURDIR}/entities
.PATH: ${.CURDIR}/ui

# source code files to be compiled
SRCS = proj.c timer.c keyboard.c mouse.c rtc.c v_card.c utils.c game.c menu.c font.c board.c background.c hud.c sunflower.c peashooter.c zombie.c sun.c projectile.c wave_manager.c name_input.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CPPFLAGS += -pedantic -D__LCOM_OPTIMIZED__ -I./drivers -I./entities -I./ui

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
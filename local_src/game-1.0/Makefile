#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CFLAGS += -O2 -g -Wall -Dlinux #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS +=

game: game.c gwint.c drawapi.c control_interface_dev.c
	gcc $^ -l GL -l glut -lncurses -lm -o $@

all: game

clean:
	-rm -f game

install:


.PHONY: all install clean

# end of development makefile

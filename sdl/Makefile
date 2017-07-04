
#BINARY		:=  vol_ctl
BINARY		:=  disc_sect

OBJS		:= $(BINARY).o
OBJS		+= ../gui_elements.o ../draw_disc_sector.o

CFLAGS 		= -g -Wall -Wextra
CFLAGS		+= -I.. -DDISPLAY_WIDTH=128

# u8g2
U8G2_DIR	:=  ../u8g2/csrc
CFLAGS		+= -I$(U8G2_DIR)  `sdl-config --cflags`
U8G2SRC		:= $(wildcard $(U8G2_DIR)/*.c) $(wildcard $(U8G2_DIR)/../sys/sdl/common/*.c)
OBJS		+= $(U8G2SRC:.c=.o)


all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) `sdl-config --libs` -o $(BINARY)

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(BINARY)

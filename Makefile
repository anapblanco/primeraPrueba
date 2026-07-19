CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99
CPPFLAGS ?=
LDFLAGS ?=
 
PKG_CONFIG ?= pkg-config
TARGET := frogger
 
SRCS := main.c game.c entities.c interactions.c levels.c allegroFrontend.c top10.c
OBJS := $(SRCS:.c=.o)
 
ALLEGRO_PKGS := allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_audio-5 allegro_primitives-5
ALLEGRO_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(ALLEGRO_PKGS) 2>/dev/null)
ALLEGRO_LIBS := $(shell $(PKG_CONFIG) --libs $(ALLEGRO_PKGS) 2>/dev/null)
 
ifeq ($(strip $(ALLEGRO_CFLAGS)$(ALLEGRO_LIBS)),)
    ALLEGRO_CFLAGS :=
    ALLEGRO_LIBS := -lallegro -lallegro_main -lallegro_font -lallegro_ttf -lallegro_image -lallegro_audio -lallegro_primitives
endif
 
.PHONY: all clean
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(ALLEGRO_LIBS)
 
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ALLEGRO_CFLAGS) -c $< -o $@
 
clean:
	rm -f $(OBJS) $(TARGET)
 
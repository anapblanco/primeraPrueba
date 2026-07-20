# Compilador y opciones
CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99
CPPFLAGS ?=
LDFLAGS ?=

# Herramienta para gestionar las dependencias de Allegro
PKG_CONFIG ?= pkg-config

# Nombre del ejecutable
TARGET := frogger

# Archivos fuente (modularizados)
SRCS := main.c game.c entities.c interactions.c levels.c \
	    frontendInit.c frontendRender.c frontendMenus.c frontendInput.c frontendCleanup.c \
	    top10.c

# Archivos objeto generados a partir de los archivos fuente
OBJS := $(SRCS:.c=.o)

# Configuración de Allegro
ALLEGRO_PKGS := allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_audio-5 allegro_primitives-5
ALLEGRO_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(ALLEGRO_PKGS) 2>/dev/null)
ALLEGRO_LIBS := $(shell $(PKG_CONFIG) --libs $(ALLEGRO_PKGS) 2>/dev/null)

# Si pkg-config no encuentra Allegro, usar valores predeterminados
ifeq ($(strip $(ALLEGRO_CFLAGS)$(ALLEGRO_LIBS)),)
	ALLEGRO_CFLAGS := -I/usr/local/include -I/opt/homebrew/include
	ALLEGRO_LIBS := -L/usr/local/lib -L/opt/homebrew/lib \
	                -lallegro -lallegro_main -lallegro_font -lallegro_ttf \
	                -lallegro_image -lallegro_audio -lallegro_primitives
endif

# Reglas principales
.PHONY: all clean

# Regla para compilar todo
all: $(TARGET)

# Regla para generar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(ALLEGRO_LIBS)

# Regla para compilar archivos fuente en archivos objeto
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ALLEGRO_CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
 
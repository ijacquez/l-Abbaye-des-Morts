all: abbaye

SRCS= \
	src/drawing.c \
	src/enemies.c \
	src/jean.c \
	src/loading.c \
\
	src/main.c \
\
	src/screen_ending.c \
	src/screen_game.c \
	src/screen_gameover.c \
	src/screen_history.c \
	src/screen_start.c \
\
	src/render_manager.c \
	src/sound_manager.c

CFLAGS+= -finline-functions -funswitch-loops -fpredictive-commoning -fgcse-after-reload -ftree-vectorize -I/mingw64/include $(shell sdl2-config --cflags)

LDFLAGS+= -L/mingw64/lib -lSDL2main -lSDL2 -mwindows -lSDL2_image -lSDL2_mixer -lm

abbaye: $(SRCS)
	gcc $(CFLAGS) $(SRCS) -o abbayev2 $(LDFLAGS)

clean:
	rm -r -f ./abbayev2

install: abbaye
	cp abbayev2.exe dll/
	cp abbaye.desktop dll/applications
	mkdir -p dll/sounds
	cp ./sounds/* dll/sounds
	mkdir -p dll/data
	cp ./data/* dll/data
	cp abbaye.png dll/pixmaps
	mkdir -p dll/graphics
	cp -r ./graphics/* dll/graphics

clib = \
	-lglfw3	\
	-lopengl32\
	-lwinmm \
	-lgdi32 \
	-lglew.dll \
	-lfreetype \
	-lws2_32 \
	-lSDL2_net \
	-lpthread
cflags = -LC:/Bin/mingw/lib -IC:/Bin/mingw/include -w

src = $(wildcard *.c) \
	$(wildcard soil/*.c) \
	$(wildcard states/*.c) \
	$(wildcard util/*.c)

all: $(src)
	gcc -o release/cgl.exe $^ $(cflags) $(clib)

clib = \
	-lglfw3	\
	-lopengl32\
	-lwinmm \
	-lgdi32 \
	-lglew.dll \
	-lfreetype
cflags = -LC:/Bin/mingw/lib -IC:/Bin/mingw/include

src = $(wildcard *.c) $(wildcard soil/*.c)# $(wildcard glmatrix/*.c)

all: $(src)
	gcc -o release/cgl.exe $^ $(cflags) $(clib)

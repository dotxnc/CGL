# clib = \
# 	-lglfw3	\
# 	-lopengl32\
# 	-lwinmm \
# 	-lgdi32 \
# 	-lglew.dll \
# 	-lfreetype \
# 	-lws2_32 \
# 	-lSDL2_net \
# 	-lpthread \
# 	-lassimp.dll
# cflags = -LC:/Bin/mingw/lib -IC:/Bin/mingw/include -w -fpermissive
# 
# src = $(wildcard src/*.c) \
# 	$(wildcard include/soil/*.c) \
# 	$(wildcard include/util/*.c)
# 
# all: $(src)
# 	


TARGET = release/libcgl.a
CC = gcc
CFLAGS = -LC:/Bin/mingw/lib -IC:/Bin/mingw/include -w -fpermissive

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c)) $(patsubst %.c, %.o, $(wildcard include/soil/*.c)) $(patsubst %.c, %.o, $(wildcard include/util/*.c))
HEADERS = $(wildcard include/*.h) $(wildcard include/soil/*.h) $(wildcard include/util/*.h)

%.o %.c: $(HEADERS)
	gcc $(CFLAGS) -c $< -o $@


.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
    # $(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	del src\\*.o
	del include\\soil\\*.o
	del include\\util\\*.o

# Build.
ifndef build
    build := release
endif
ifeq ($(build), debug)
    CXXFLAGS += -g -DDEBUG
else ifeq ($(build), release)
    CXXFLAGS += -O3 -DNDEBUG
else
    $(error Invalid build "$(build)", please specify "debug" or "release")
endif

# Platform.
ifndef platform
    # TODO: Autodetect.
    platform := mac
endif
ifeq ($(platform), mac)
    CPPFLAGS += -I/usr/local/include/SDL -I/opt/local/include
    LDFLAGS += -framework OpenGL -L/usr/local/lib -lSDL
else
    $(error Invalid platform "$(platform)", only "mac" is supported for now)
endif

objects := \
    block.o \
    character.o \
    debug_graphics.o \
	game_screen.o \
	geometry.o \
	main.o \
	screen.o \
	title_screen.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

block.o: block.hpp geometry.hpp debug_graphics.hpp
character.o: character.hpp geometry.hpp debug_graphics.hpp
debug_graphics.o: debug_graphics.hpp geometry.hpp
game_screen.o: game_screen.hpp screen.hpp geometry.hpp block.hpp
game_screen.o: character.hpp debug_graphics.hpp
geometry.o: geometry.hpp
main.o: title_screen.hpp screen.hpp
screen.o: screen.hpp
title_screen.o: title_screen.hpp screen.hpp game_screen.hpp geometry.hpp

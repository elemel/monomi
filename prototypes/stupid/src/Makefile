# External dependencies.
BOOST_INCLUDE_DIR := ext/boost/include
BOOST_LIB_DIR := ext/boost/lib
BOX2D_INCLUDE_DIR := ext/box2d/include
BOX2D_LIB_DIR := ext/box2d/lib
SDL_INCLUDE_DIR := ext/sdl/include
SDL_LIB_DIR := ext/sdl/lib

# Build variant.
VARIANT := debug
ifeq ($(VARIANT), debug)
	CXXFLAGS += -g -DDEBUG
else ifeq ($(VARIANT), release)
	CXXFLAGS += -O3 -DNDEBUG
else
	$(error Invalid build variant "$(VARIANT)", please specify "debug" or "release")
endif

# Build platform.
# TODO: Autodetect.
PLATFORM := mac
ifeq ($(PLATFORM), mac)
	CPPFLAGS += -I$(BOOST_INCLUDE_DIR) -I$(BOX2D_INCLUDE_DIR) -I$(SDL_INCLUDE_DIR)
	LDFLAGS += -L$(BOX2D_LIB_DIR) -lBox2D -L$(SDL_LIB_DIR) -lSDL -framework OpenGL
else
	$(error Invalid build platform "$(PLATFORM)", only "mac" is supported for now)
endif

objects := \
	debug_graphics.o \
	game_logic.o \
	game_loop.o \
	main.o \
	stringer.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

game_loop.o: game_loop.hpp
main.o: game_loop.hpp stringer.hpp
stringer.o: stringer.hpp

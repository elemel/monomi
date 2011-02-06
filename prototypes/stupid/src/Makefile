# External dependencies.
BOOST_INCLUDE_DIR := ext/boost/include
BOOST_LIB_DIR := ext/boost/lib
BOX2D_INCLUDE_DIR := ext/box2d/include
BOX2D_LIB_DIR := ext/box2d/lib
RAPIDXML_INCLUDE_DIR := ext/rapidxml/include
SDL_INCLUDE_DIR := ext/sdl/include
SDL_LIB_DIR := ext/sdl/lib

# Build variant.
VARIANT := debug
ifeq ($(VARIANT), debug)
	CXXFLAGS += -g -DDEBUG -W -Wall -Wextra -Werror
else ifeq ($(VARIANT), release)
	CXXFLAGS += -O3 -DNDEBUG
else
	$(error Invalid build variant "$(VARIANT)", please specify "debug" or "release")
endif

# Build platform.
#
# TODO: Autodetect.
PLATFORM := mac
ifeq ($(PLATFORM), mac)
	CPPFLAGS += -I$(BOOST_INCLUDE_DIR) -I$(BOX2D_INCLUDE_DIR) -I$(RAPIDXML_INCLUDE_DIR) -I$(SDL_INCLUDE_DIR)
	LDFLAGS += -L$(BOX2D_LIB_DIR) -lBox2D -L$(SDL_LIB_DIR) -lSDL -framework OpenGL
else
	$(error Invalid build platform "$(PLATFORM)", only "mac" is supported for now)
endif

objects := \
	color.o \
	debug_graphics.o \
	game_logic.o \
	game_loop.o \
	geometry.o \
	main.o \
	physics_debug_graphics_adapter.o \
	string_buffer.o \
	svg_parser.o \
	svg_path_parser.o \
	svg_style_parser.o \
	svg_transform_parser.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

color.o: color.hpp
debug_graphics.o: debug_graphics.hpp
game_logic.o: game_logic.hpp character_actor.hpp actor.hpp geometry.hpp
game_logic.o: physics_debug_graphics_adapter.hpp
game_loop.o: game_loop.hpp debug_graphics.hpp game_logic.hpp
game_loop.o: character_actor.hpp actor.hpp geometry.hpp
geometry.o: geometry.hpp
main.o: color.hpp game_logic.hpp character_actor.hpp actor.hpp geometry.hpp
main.o: game_loop.hpp string_buffer.hpp svg_parser.hpp svg_path_parser.hpp
main.o: svg_style_parser.hpp svg_transform_parser.hpp
physics_debug_graphics_adapter.o: physics_debug_graphics_adapter.hpp
physics_debug_graphics_adapter.o: debug_graphics.hpp
string_buffer.o: string_buffer.hpp
svg_parser.o: svg_parser.hpp color.hpp geometry.hpp svg_path_parser.hpp
svg_parser.o: svg_style_parser.hpp svg_transform_parser.hpp string_buffer.hpp
svg_path_parser.o: svg_path_parser.hpp geometry.hpp string_buffer.hpp
svg_style_parser.o: svg_style_parser.hpp geometry.hpp string_buffer.hpp
svg_transform_parser.o: svg_transform_parser.hpp geometry.hpp
svg_transform_parser.o: string_buffer.hpp

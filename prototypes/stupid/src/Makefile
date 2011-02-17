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
	capitalize.o \
	character_actor.o \
	character_states.o \
	color.o \
	debug_graphics.o \
	game_logic.o \
	game_loop.o \
	geometry.o \
	main.o \
	physics_debug_graphics_adapter.o \
	string_buffer.o \
	support_flag.o \
	svg_parser.o \
	svg_path_parser.o \
	svg_style_parser.o \
	svg_transform_parser.o \
	type.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

capitalize.o: capitalize.hpp
character_actor.o: character_actor.hpp actor.hpp category_flag.hpp
character_actor.o: geometry.hpp input_flag.hpp support_flag.hpp
character_actor.o: capitalize.hpp character_states.hpp state.hpp
character_actor.o: state_fwd.hpp game_logic.hpp print_flags.hpp type.hpp
character_states.o: character_states.hpp state.hpp state_fwd.hpp
character_states.o: character_actor.hpp actor.hpp category_flag.hpp
character_states.o: geometry.hpp input_flag.hpp support_flag.hpp
color.o: color.hpp
debug_graphics.o: debug_graphics.hpp
game_logic.o: game_logic.hpp category_flag.hpp geometry.hpp
game_logic.o: character_actor.hpp actor.hpp input_flag.hpp support_flag.hpp
game_logic.o: character_states.hpp state.hpp state_fwd.hpp
game_logic.o: physics_debug_graphics_adapter.hpp
game_loop.o: game_loop.hpp character_actor.hpp actor.hpp category_flag.hpp
game_loop.o: geometry.hpp input_flag.hpp support_flag.hpp debug_graphics.hpp
game_loop.o: game_logic.hpp
geometry.o: geometry.hpp
main.o: color.hpp game_logic.hpp category_flag.hpp geometry.hpp game_loop.hpp
main.o: string_buffer.hpp svg_parser.hpp svg_path_parser.hpp
main.o: svg_style_parser.hpp svg_transform_parser.hpp
physics_debug_graphics_adapter.o: physics_debug_graphics_adapter.hpp
physics_debug_graphics_adapter.o: debug_graphics.hpp
string_buffer.o: string_buffer.hpp
support_flag.o: support_flag.hpp
svg_parser.o: svg_parser.hpp color.hpp geometry.hpp svg_path_parser.hpp
svg_parser.o: svg_style_parser.hpp svg_transform_parser.hpp string_buffer.hpp
svg_path_parser.o: svg_path_parser.hpp geometry.hpp string_buffer.hpp
svg_style_parser.o: svg_style_parser.hpp geometry.hpp string_buffer.hpp
svg_transform_parser.o: svg_transform_parser.hpp geometry.hpp
svg_transform_parser.o: string_buffer.hpp
type.o: type.hpp

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
endif

# Build platform.
#
# TODO: Autodetect.
PLATFORM := mac
ifeq ($(PLATFORM), mac)
	CPPFLAGS += -I$(BOOST_INCLUDE_DIR) -I$(BOX2D_INCLUDE_DIR) -I$(RAPIDXML_INCLUDE_DIR) -I$(SDL_INCLUDE_DIR)
	LDFLAGS += -L$(BOX2D_LIB_DIR) -lBox2D -L$(SDL_LIB_DIR) -lSDL -framework OpenGL
endif

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: all
all: monomi

.PHONY: run
run: monomi
	./monomi

.PHONY: depend
depend:
	makedepend -- $(CXXFLAGS) -- $(SRCS) > depend.log 2>&1

.PHONY: clean
clean:
	rm -fr monomi monomi.dSYM $(OBJS)

monomi: $(OBJS)
	g++ -o monomi $(OBJS) $(LDFLAGS)

# DO NOT DELETE

capitalize.o: capitalize.hpp
character_actor.o: character_actor.hpp actor.hpp category_flag.hpp
character_actor.o: character_control_flag.hpp character_sensor_flag.hpp
character_actor.o: character_type.hpp character_technique_flag.hpp
character_actor.o: character_tool_flag.hpp geometry.hpp state_fwd.hpp
character_actor.o: capitalize.hpp character_states.hpp state.hpp
character_actor.o: game_logic.hpp print_flags.hpp type.hpp
character_config_loader.o: character_config_loader.hpp game_logic.hpp
character_config_loader.o: category_flag.hpp character_type.hpp
character_config_loader.o: character_technique_flag.hpp
character_config_loader.o: character_tool_flag.hpp geometry.hpp
character_sensor_flag.o: character_sensor_flag.hpp
character_states.o: character_states.hpp state.hpp state_fwd.hpp
character_states.o: character_actor.hpp actor.hpp category_flag.hpp
character_states.o: character_control_flag.hpp character_sensor_flag.hpp
character_states.o: character_type.hpp character_technique_flag.hpp
character_states.o: character_tool_flag.hpp geometry.hpp
color.o: color.hpp
debug_graphics.o: debug_graphics.hpp
game_logic.o: game_logic.hpp category_flag.hpp character_type.hpp
game_logic.o: character_technique_flag.hpp character_tool_flag.hpp
game_logic.o: geometry.hpp character_actor.hpp actor.hpp
game_logic.o: character_control_flag.hpp character_sensor_flag.hpp
game_logic.o: state_fwd.hpp character_states.hpp state.hpp
game_logic.o: physics_debug_graphics_adapter.hpp
game_loop.o: game_loop.hpp character_actor.hpp actor.hpp category_flag.hpp
game_loop.o: character_control_flag.hpp character_sensor_flag.hpp
game_loop.o: character_type.hpp character_technique_flag.hpp
game_loop.o: character_tool_flag.hpp geometry.hpp state_fwd.hpp
game_loop.o: debug_graphics.hpp game_logic.hpp
geometry.o: geometry.hpp
level_loader.o: level_loader.hpp color.hpp geometry.hpp svg_parser.hpp
level_loader.o: svg_path_parser.hpp svg_style_parser.hpp
level_loader.o: svg_transform_parser.hpp game_logic.hpp category_flag.hpp
level_loader.o: character_type.hpp character_technique_flag.hpp
level_loader.o: character_tool_flag.hpp
main.o: character_config_loader.hpp character_type.hpp
main.o: character_technique_flag.hpp character_tool_flag.hpp color.hpp
main.o: game_logic.hpp category_flag.hpp geometry.hpp game_loop.hpp
main.o: level_loader.hpp svg_parser.hpp svg_path_parser.hpp
main.o: svg_style_parser.hpp svg_transform_parser.hpp string_buffer.hpp
physics_debug_graphics_adapter.o: physics_debug_graphics_adapter.hpp
physics_debug_graphics_adapter.o: debug_graphics.hpp
string_buffer.o: string_buffer.hpp
svg_parser.o: svg_parser.hpp color.hpp geometry.hpp svg_path_parser.hpp
svg_parser.o: svg_style_parser.hpp svg_transform_parser.hpp string_buffer.hpp
svg_path_parser.o: svg_path_parser.hpp geometry.hpp string_buffer.hpp
svg_style_parser.o: svg_style_parser.hpp geometry.hpp string_buffer.hpp
svg_transform_parser.o: svg_transform_parser.hpp geometry.hpp
svg_transform_parser.o: string_buffer.hpp
type.o: type.hpp

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
	actor.o \
	block_actor.o \
	camera.o \
	character_actor.o \
	character_collision_component.o \
	character_factory.o \
	character_jump_state.o \
	character_physics_component.o \
	character_state_component.o \
	character_type.o \
	character_walk_state.o \
	character_wall_slide_state.o \
	component_registry.o \
	debug_color.o \
	debug_graphics.o \
	game.o \
	game_screen.o \
	geometry.o \
	main.o \
	random.o \
	screen.o \
	title_screen.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

actor.o: actor.hpp
block_actor.o: block_actor.hpp actor.hpp geometry.hpp debug_graphics.hpp
block_actor.o: debug_color.hpp
camera.o: camera.hpp geometry.hpp
character_actor.o: character_actor.hpp actor.hpp control.hpp geometry.hpp
character_actor.o: technique.hpp tool.hpp character_physics_component.hpp
character_actor.o: component.hpp character_type.hpp debug_graphics.hpp
character_actor.o: debug_color.hpp
character_collision_component.o: character_collision_component.hpp
character_collision_component.o: component.hpp character_actor.hpp actor.hpp
character_collision_component.o: control.hpp geometry.hpp technique.hpp
character_collision_component.o: tool.hpp game.hpp component_registry.hpp
character_factory.o: character_factory.hpp character_tag.hpp
character_factory.o: character_actor.hpp actor.hpp control.hpp geometry.hpp
character_factory.o: technique.hpp tool.hpp character_collision_component.hpp
character_factory.o: component.hpp character_physics_component.hpp
character_factory.o: character_state_component.hpp character_type.hpp
character_factory.o: character_walk_state.hpp state.hpp
character_jump_state.o: character_jump_state.hpp geometry.hpp state.hpp
character_jump_state.o: character_actor.hpp actor.hpp control.hpp
character_jump_state.o: technique.hpp tool.hpp character_type.hpp
character_jump_state.o: character_walk_state.hpp
character_jump_state.o: character_wall_slide_state.hpp
character_physics_component.o: character_physics_component.hpp component.hpp
character_physics_component.o: block_actor.hpp actor.hpp geometry.hpp
character_physics_component.o: character_actor.hpp control.hpp technique.hpp
character_physics_component.o: tool.hpp character_type.hpp game.hpp
character_physics_component.o: component_registry.hpp
character_state_component.o: character_state_component.hpp component.hpp
character_state_component.o: character_actor.hpp actor.hpp control.hpp
character_state_component.o: geometry.hpp technique.hpp tool.hpp state.hpp
character_type.o: character_type.hpp geometry.hpp technique.hpp tool.hpp
character_walk_state.o: character_walk_state.hpp state.hpp
character_walk_state.o: character_actor.hpp actor.hpp control.hpp
character_walk_state.o: geometry.hpp technique.hpp tool.hpp
character_walk_state.o: character_jump_state.hpp character_type.hpp
character_wall_slide_state.o: character_wall_slide_state.hpp state.hpp
character_wall_slide_state.o: character_actor.hpp actor.hpp control.hpp
character_wall_slide_state.o: geometry.hpp technique.hpp tool.hpp
character_wall_slide_state.o: character_jump_state.hpp character_type.hpp
character_wall_slide_state.o: character_walk_state.hpp
component_registry.o: component_registry.hpp component.hpp
debug_color.o: debug_color.hpp
debug_graphics.o: debug_graphics.hpp debug_color.hpp geometry.hpp
game.o: game.hpp component_registry.hpp block_actor.hpp actor.hpp
game.o: geometry.hpp character_actor.hpp control.hpp technique.hpp tool.hpp
game.o: character_factory.hpp character_tag.hpp character_type.hpp
game.o: component.hpp random.hpp
game_screen.o: game_screen.hpp camera.hpp geometry.hpp screen.hpp
game_screen.o: block_actor.hpp actor.hpp character_actor.hpp control.hpp
game_screen.o: technique.hpp tool.hpp debug_graphics.hpp debug_color.hpp
game_screen.o: game.hpp component_registry.hpp random.hpp
geometry.o: geometry.hpp
main.o: title_screen.hpp screen.hpp
random.o: random.hpp
screen.o: screen.hpp
title_screen.o: title_screen.hpp screen.hpp game_screen.hpp camera.hpp
title_screen.o: geometry.hpp

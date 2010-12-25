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
	LDFLAGS += -framework OpenGL -L/usr/local/lib -lSDL -L/opt/local/lib -lboost_signals-mt
else
	$(error Invalid platform "$(platform)", only "mac" is supported for now)
endif

objects := \
	actor.o \
	block_actor.o \
	camera.o \
	character_actor.o \
	character_air_jump_state.o \
	character_factory.o \
	character_fall_state.o \
	character_jump_state.o \
	character_type.o \
	character_wall_jump_state.o \
	character_walk_state.o \
	character_wall_slide_state.o \
	debug_color.o \
	debug_graphics.o \
	game.o \
	game_screen.o \
	geometry.o \
	main.o \
	random.o \
	screen.o \
	state_machine.o \
	title_screen.o \
	type.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

actor.o: actor.hpp
block_actor.o: block_actor.hpp actor.hpp geometry.hpp debug_graphics.hpp
block_actor.o: debug_color.hpp
camera.o: camera.hpp geometry.hpp
character_actor.o: character_actor.hpp actor.hpp geometry.hpp input.hpp
character_actor.o: technique.hpp tool.hpp block_actor.hpp character_type.hpp
character_actor.o: debug_graphics.hpp debug_color.hpp game.hpp
character_actor.o: state_machine.hpp state.hpp type.hpp
character_air_jump_state.o: character_air_jump_state.hpp state.hpp
character_air_jump_state.o: character_actor.hpp actor.hpp geometry.hpp
character_air_jump_state.o: input.hpp technique.hpp tool.hpp
character_air_jump_state.o: character_fall_state.hpp character_type.hpp
character_factory.o: character_factory.hpp character_tag.hpp
character_factory.o: character_actor.hpp actor.hpp geometry.hpp input.hpp
character_factory.o: technique.hpp tool.hpp character_fall_state.hpp
character_factory.o: state.hpp character_type.hpp state_machine.hpp
character_fall_state.o: character_fall_state.hpp state.hpp
character_fall_state.o: character_actor.hpp actor.hpp geometry.hpp input.hpp
character_fall_state.o: technique.hpp tool.hpp character_air_jump_state.hpp
character_fall_state.o: character_jump_state.hpp character_type.hpp
character_fall_state.o: character_walk_state.hpp
character_fall_state.o: character_wall_slide_state.hpp
character_jump_state.o: character_jump_state.hpp state.hpp
character_jump_state.o: character_actor.hpp actor.hpp geometry.hpp input.hpp
character_jump_state.o: technique.hpp tool.hpp character_fall_state.hpp
character_jump_state.o: character_type.hpp
character_type.o: character_type.hpp geometry.hpp technique.hpp tool.hpp
character_walk_state.o: character_walk_state.hpp state.hpp
character_walk_state.o: character_actor.hpp actor.hpp geometry.hpp input.hpp
character_walk_state.o: technique.hpp tool.hpp character_fall_state.hpp
character_walk_state.o: character_jump_state.hpp character_type.hpp
character_wall_jump_state.o: character_wall_jump_state.hpp state.hpp
character_wall_jump_state.o: character_actor.hpp actor.hpp geometry.hpp
character_wall_jump_state.o: input.hpp technique.hpp tool.hpp
character_wall_jump_state.o: character_fall_state.hpp character_type.hpp
character_wall_slide_state.o: character_wall_slide_state.hpp state.hpp
character_wall_slide_state.o: character_actor.hpp actor.hpp geometry.hpp
character_wall_slide_state.o: input.hpp technique.hpp tool.hpp
character_wall_slide_state.o: character_fall_state.hpp character_type.hpp
character_wall_slide_state.o: character_walk_state.hpp
character_wall_slide_state.o: character_wall_jump_state.hpp
debug_color.o: debug_color.hpp
debug_graphics.o: debug_graphics.hpp debug_color.hpp geometry.hpp
game.o: game.hpp block_actor.hpp actor.hpp geometry.hpp character_actor.hpp
game.o: input.hpp technique.hpp tool.hpp character_factory.hpp
game.o: character_tag.hpp character_type.hpp random.hpp
game_screen.o: game_screen.hpp camera.hpp geometry.hpp screen.hpp
game_screen.o: block_actor.hpp actor.hpp character_actor.hpp input.hpp
game_screen.o: technique.hpp tool.hpp debug_graphics.hpp debug_color.hpp
game_screen.o: game.hpp random.hpp
geometry.o: geometry.hpp
main.o: title_screen.hpp screen.hpp
random.o: random.hpp
screen.o: screen.hpp
state_machine.o: state_machine.hpp state.hpp type.hpp
title_screen.o: title_screen.hpp screen.hpp game_screen.hpp camera.hpp
title_screen.o: geometry.hpp
type.o: type.hpp

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
	LDFLAGS += -framework OpenGL -L/usr/local/lib -lSDL -L/opt/local/lib
else
	$(error Invalid platform "$(platform)", only "mac" is supported for now)
endif

objects := \
	actor.o \
	block_actor.o \
	camera.o \
	category_pattern.o \
	character_actor.o \
	character_air_jump_state.o \
	character_factory.o \
	character_fall_state.o \
	character_jump_state.o \
	character_type.o \
	character_wall_jump_state.o \
	character_walk_state.o \
	character_wall_slide_state.o \
	collision_body.o \
	collision_detector.o \
	collision_shape.o \
	debug_color.o \
	debug_graphics.o \
	game.o \
	game_screen.o \
	geometry.o \
	grid.o \
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

actor.o: actor.hpp actor_fwd.hpp priority.hpp
block_actor.o: block_actor.hpp actor.hpp actor_fwd.hpp priority.hpp
block_actor.o: geometry.hpp debug_graphics.hpp debug_color.hpp
camera.o: camera.hpp geometry.hpp
category_pattern.o: category_pattern.hpp category.hpp
character_actor.o: character_actor.hpp actor.hpp actor_fwd.hpp priority.hpp
character_actor.o: contact.hpp geometry.hpp input.hpp technique.hpp tool.hpp
character_actor.o: block_actor.hpp character_type.hpp debug_graphics.hpp
character_actor.o: debug_color.hpp game.hpp state.hpp state_fwd.hpp
character_actor.o: state_machine.hpp type.hpp
character_air_jump_state.o: character_air_jump_state.hpp state.hpp
character_air_jump_state.o: state_fwd.hpp character_actor.hpp actor.hpp
character_air_jump_state.o: actor_fwd.hpp priority.hpp contact.hpp
character_air_jump_state.o: geometry.hpp input.hpp technique.hpp tool.hpp
character_air_jump_state.o: character_fall_state.hpp character_type.hpp
character_factory.o: character_factory.hpp character_tag.hpp
character_factory.o: character_actor.hpp actor.hpp actor_fwd.hpp priority.hpp
character_factory.o: contact.hpp geometry.hpp input.hpp technique.hpp
character_factory.o: tool.hpp character_fall_state.hpp state.hpp
character_factory.o: state_fwd.hpp character_type.hpp state_machine.hpp
character_fall_state.o: character_fall_state.hpp state.hpp state_fwd.hpp
character_fall_state.o: character_actor.hpp actor.hpp actor_fwd.hpp
character_fall_state.o: priority.hpp contact.hpp geometry.hpp input.hpp
character_fall_state.o: technique.hpp tool.hpp character_air_jump_state.hpp
character_fall_state.o: character_jump_state.hpp character_type.hpp
character_fall_state.o: character_walk_state.hpp
character_fall_state.o: character_wall_slide_state.hpp
character_jump_state.o: character_jump_state.hpp state.hpp state_fwd.hpp
character_jump_state.o: character_actor.hpp actor.hpp actor_fwd.hpp
character_jump_state.o: priority.hpp contact.hpp geometry.hpp input.hpp
character_jump_state.o: technique.hpp tool.hpp character_fall_state.hpp
character_jump_state.o: character_type.hpp
character_type.o: character_type.hpp geometry.hpp technique.hpp tool.hpp
character_walk_state.o: character_walk_state.hpp state.hpp state_fwd.hpp
character_walk_state.o: character_actor.hpp actor.hpp actor_fwd.hpp
character_walk_state.o: priority.hpp contact.hpp geometry.hpp input.hpp
character_walk_state.o: technique.hpp tool.hpp character_fall_state.hpp
character_walk_state.o: character_jump_state.hpp character_type.hpp
character_wall_jump_state.o: character_wall_jump_state.hpp state.hpp
character_wall_jump_state.o: state_fwd.hpp character_actor.hpp actor.hpp
character_wall_jump_state.o: actor_fwd.hpp priority.hpp contact.hpp
character_wall_jump_state.o: geometry.hpp input.hpp technique.hpp tool.hpp
character_wall_jump_state.o: character_fall_state.hpp character_type.hpp
character_wall_slide_state.o: character_wall_slide_state.hpp state.hpp
character_wall_slide_state.o: state_fwd.hpp character_actor.hpp actor.hpp
character_wall_slide_state.o: actor_fwd.hpp priority.hpp contact.hpp
character_wall_slide_state.o: geometry.hpp input.hpp technique.hpp tool.hpp
character_wall_slide_state.o: character_fall_state.hpp character_type.hpp
character_wall_slide_state.o: character_walk_state.hpp
character_wall_slide_state.o: character_wall_jump_state.hpp
collision_body.o: collision_body.hpp collision_body_fwd.hpp actor_fwd.hpp
collision_body.o: geometry.hpp collision_detector.hpp
collision_body.o: collision_detector_fwd.hpp collision_shape.hpp
collision_body.o: collision_shape_fwd.hpp
collision_detector.o: collision_detector.hpp collision_detector_fwd.hpp
collision_detector.o: collision_body.hpp collision_body_fwd.hpp actor_fwd.hpp
collision_detector.o: geometry.hpp collision_shape.hpp
collision_detector.o: collision_shape_fwd.hpp
collision_shape.o: collision_shape.hpp collision_shape_fwd.hpp actor_fwd.hpp
collision_shape.o: geometry.hpp collision_body.hpp collision_body_fwd.hpp
debug_color.o: debug_color.hpp
debug_graphics.o: debug_graphics.hpp debug_color.hpp geometry.hpp
game.o: game.hpp actor_fwd.hpp block_actor.hpp actor.hpp priority.hpp
game.o: geometry.hpp character_actor.hpp contact.hpp input.hpp technique.hpp
game.o: tool.hpp character_factory.hpp character_tag.hpp character_type.hpp
game_screen.o: game_screen.hpp camera.hpp geometry.hpp random.hpp screen.hpp
game_screen.o: block_actor.hpp actor.hpp actor_fwd.hpp priority.hpp
game_screen.o: character_actor.hpp contact.hpp input.hpp technique.hpp
game_screen.o: tool.hpp debug_graphics.hpp debug_color.hpp game.hpp
geometry.o: geometry.hpp
grid.o: grid.hpp geometry.hpp
main.o: title_screen.hpp screen.hpp
random.o: random.hpp
screen.o: screen.hpp
state_machine.o: state_machine.hpp state_fwd.hpp state.hpp type.hpp
title_screen.o: title_screen.hpp screen.hpp game_screen.hpp camera.hpp
title_screen.o: geometry.hpp random.hpp
type.o: type.hpp

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
	block.o \
	camera.o \
	character.o \
	character_factory.o \
	character_type.o \
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
block.o: block.hpp actor.hpp geometry.hpp debug_graphics.hpp
camera.o: camera.hpp geometry.hpp
character.o: character.hpp actor.hpp control.hpp geometry.hpp technique.hpp
character.o: tool.hpp character_type.hpp debug_graphics.hpp
character_factory.o: character_factory.hpp character.hpp actor.hpp
character_factory.o: control.hpp geometry.hpp technique.hpp tool.hpp
character_factory.o: character_type.hpp
character_type.o: character_type.hpp geometry.hpp technique.hpp tool.hpp
debug_graphics.o: debug_graphics.hpp geometry.hpp
game_screen.o: game_screen.hpp camera.hpp geometry.hpp screen.hpp block.hpp
game_screen.o: actor.hpp character.hpp control.hpp technique.hpp tool.hpp
game_screen.o: character_factory.hpp character_type.hpp debug_graphics.hpp
game_screen.o: random.hpp
geometry.o: geometry.hpp
main.o: title_screen.hpp screen.hpp
random.o: random.hpp
screen.o: screen.hpp
title_screen.o: title_screen.hpp screen.hpp game_screen.hpp camera.hpp
title_screen.o: geometry.hpp

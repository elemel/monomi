# Build.
ifndef build
	build := debug
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
	CPPFLAGS += -Iext/sdl/include -I/opt/local/include
	LDFLAGS += -framework OpenGL -Lext/sdl/lib -lSDL
else
	$(error Invalid platform "$(platform)", only "mac" is supported for now)
endif

objects := \
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

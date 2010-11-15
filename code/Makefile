CPPFLAGS := -I/opt/local/include -I/usr/local/include/SDL
CXXFLAGS := -g
LDFLAGS := -framework OpenGL -lSDL

objects := \
	actor.o \
	debug_graphics.o \
	game_engine.o \
	game_screen.o \
	geometry.o \
	keys.o \
	main.o \
	opengl_debug_graphics.o \
	screen.o \
	sdl_window.o \
	window.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

actor.o: actor.hpp
debug_graphics.o: debug_graphics.hpp
game_engine.o: game_engine.hpp actor.hpp opengl_debug_graphics.hpp
game_engine.o: debug_graphics.hpp geometry.hpp
game_screen.o: game_screen.hpp screen.hpp keys.hpp game_engine.hpp window.hpp
geometry.o: geometry.hpp
keys.o: keys.hpp
main.o: game_screen.hpp screen.hpp keys.hpp sdl_window.hpp window.hpp
opengl_debug_graphics.o: opengl_debug_graphics.hpp debug_graphics.hpp
opengl_debug_graphics.o: geometry.hpp
screen.o: screen.hpp keys.hpp
sdl_window.o: sdl_window.hpp window.hpp screen.hpp keys.hpp
window.o: window.hpp

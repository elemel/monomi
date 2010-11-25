CPPFLAGS := -I/opt/local/include
CXXFLAGS := -g
LDFLAGS := -framework OpenGL -lSDL

objects := \
    block.o \
    character.o \
    debug_graphics.o \
	game_screen.o \
	geometry.o \
	main.o \
	screen.o \
	title_screen.o

monomi: $(objects)
	g++ -o monomi $(objects) $(LDFLAGS)

clean:
	rm -fr monomi monomi.dSYM $(objects)

# DO NOT DELETE

block.o: block.hpp geometry.hpp debug_graphics.hpp
character.o: character.hpp geometry.hpp debug_graphics.hpp
debug_graphics.o: debug_graphics.hpp geometry.hpp
game_screen.o: game_screen.hpp screen.hpp geometry.hpp block.hpp
game_screen.o: character.hpp debug_graphics.hpp
geometry.o: geometry.hpp
main.o: title_screen.hpp screen.hpp
screen.o: screen.hpp
title_screen.o: title_screen.hpp screen.hpp game_screen.hpp geometry.hpp

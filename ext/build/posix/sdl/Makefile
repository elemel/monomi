SDL_DIR := ../../../sdl

all: include.made lib.made

include.made:
	rm -fr include
	mkdir include
	cp $(SDL_DIR)/include/*.h include
	cp include/SDL_config_macosx.h include/SDL_config.h
	touch include.made

lib.made: build.made
	rm -fr lib
	mkdir lib
	cp $(SDL_DIR)/build/.libs/libSDL.dylib lib
	install_name_tool -id `pwd`/lib/libSDL.dylib lib/libSDL.dylib
	touch lib.made

build.made:
	cd $(SDL_DIR) && sh build-scripts/fatbuild.sh
	touch build.made

clean:
	rm *.made

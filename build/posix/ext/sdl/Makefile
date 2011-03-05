SDL_EXT_DIR := ../../../../ext/sdl-1.3.0-5421
SDL_INCLUDE_DIR := $(SDL_EXT_DIR)/include
SDL_LIB_DIR := $(SDL_EXT_DIR)/lib
SDL_SRC_DIR := $(SDL_EXT_DIR)/src

all: include.made lib.made

include.made:
	rm -fr $(SDL_INCLUDE_DIR)
	mkdir $(SDL_INCLUDE_DIR)
	cp $(SDL_SRC_DIR)/include/*.h $(SDL_INCLUDE_DIR)
	cp $(SDL_INCLUDE_DIR)/SDL_config_macosx.h $(SDL_INCLUDE_DIR)/SDL_config.h
	touch include.made

lib.made: build.made
	rm -fr $(SDL_LIB_DIR)
	mkdir $(SDL_LIB_DIR)
	cp src/build/.libs/libSDL.dylib $(SDL_LIB_DIR)
	install_name_tool -id `cd $(SDL_LIB_DIR) && pwd`/libSDL.dylib $(SDL_LIB_DIR)/libSDL.dylib
	touch lib.made

build.made: copy.made
	cd src && sh build-scripts/fatbuild.sh
	touch build.made

copy.made:
	rm -fr src
	cp -r $(SDL_SRC_DIR) src
	touch copy.made

clean:
	rm src *.made

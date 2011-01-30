install.made: build.made
	rm -fr include lib
	mkdir include lib
	cp src/include/*.h include
	cp include/SDL_config_macosx.h include/SDL_config.h
	cp src/build/libSDL.la lib
	touch install.made

build.made: extract.made
	cd src && sh build-scripts/fatbuild.sh
	touch build.made

extract.made: download.made
	rm -fr src
	mkdir src
	tar xzf src.tar.gz -C src --strip-components 1
	touch extract.made

download.made:
	rm -fr src.tar.gz
	wget -O src.tar.gz http://www.libsdl.org/tmp/SDL-1.3.tar.gz
	touch download.made

clean:
	rm -fr src src.tar.gz *.made

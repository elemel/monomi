BOX2D_EXT_DIR := ../../../../ext/box2d-2.2.0-149
BOX2D_INCLUDE_DIR := $(BOX2D_EXT_DIR)/include
BOX2D_LIB_DIR := $(BOX2D_EXT_DIR)/lib
BOX2D_SRC_DIR := $(BOX2D_EXT_DIR)/src

all: include.made lib.made

include.made:
	rm -fr $(BOX2D_INCLUDE_DIR)
	mkdir $(BOX2D_INCLUDE_DIR)
	( cd $(BOX2D_SRC_DIR)/Box2D && tar -cf - `find Box2D -name "*.h" -print` ) | ( cd $(BOX2D_INCLUDE_DIR) && tar xBf - )
	touch include.made

lib.made: build.made
	rm -fr $(BOX2D_LIB_DIR)
	mkdir $(BOX2D_LIB_DIR)
	cp src/Box2D/Box2D/libBox2D.a $(BOX2D_LIB_DIR)
	touch lib.made

build.made: copy.made
	cd src/Box2D && cmake -G "Unix Makefiles" && make Box2D
	touch build.made

copy.made:
	rm -fr src
	cp -r $(BOX2D_SRC_DIR) src
	touch copy.made

clean:
	rm -fr src *.made

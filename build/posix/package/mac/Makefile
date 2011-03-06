include ../../Makefile.config

ROOT_DIR := ../../../..
ASSETS_DIR := $(ROOT_DIR)/assets
APP_DIR := Monomi.app
SDL_LIB_DIR := $(ROOT_DIR)/ext/sdl-$(SDL_VERSION)/lib
SDL_INSTALL_NAME := @executable_path/../Frameworks/libSDL.dylib

all: image.made

image.made: app.made
	rm -f Monomi.dmg
	hdiutil create -srcfolder $(APP_DIR) -volname Monomi Monomi.dmg

app.made:
	rm -fr $(APP_DIR)
	mkdir $(APP_DIR)
	mkdir $(APP_DIR)/Contents
	cp Info.plist $(APP_DIR)/Contents
	mkdir $(APP_DIR)/Contents/MacOS
	cp ../../release/monomi $(APP_DIR)/Contents/MacOS
	install_name_tool -change `sh print_install_name.sh libSDL.dylib $(APP_DIR)/Contents/MacOS/monomi` $(SDL_INSTALL_NAME) $(APP_DIR)/Contents/MacOS/monomi
	cp launch.sh $(APP_DIR)/Contents/MacOS
	chmod a+x $(APP_DIR)/Contents/MacOS/launch.sh
	mkdir $(APP_DIR)/Contents/Resources
	cp -r $(ASSETS_DIR)/* $(APP_DIR)/Contents/Resources
	mkdir $(APP_DIR)/Contents/Frameworks
	cp $(SDL_LIB_DIR)/libSDL.dylib $(APP_DIR)/Contents/Frameworks
	install_name_tool -id $(SDL_INSTALL_NAME) $(APP_DIR)/Contents/Frameworks/libSDL.dylib
	touch app.made

run: app.made
	open $(APP_DIR)

clean:
	rm -fr $(APP_DIR) Monomi.dmg *.made

.PHONY: all clean run

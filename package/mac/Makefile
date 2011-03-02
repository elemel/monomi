APP_DIR := Monomi.app
SDL_INSTALL_NAME := @executable_path/../Frameworks/libSDL.dylib

all: app.made

app.made:
	rm -fr $(APP_DIR)
	mkdir $(APP_DIR)
	mkdir $(APP_DIR)/Contents
	cp Info.plist $(APP_DIR)/Contents
	mkdir $(APP_DIR)/Contents/MacOS
	cp ../../build/posix/release/monomi $(APP_DIR)/Contents/MacOS
	install_name_tool -change `sh print_install_name.sh libSDL.dylib $(APP_DIR)/Contents/MacOS/monomi` $(SDL_INSTALL_NAME) $(APP_DIR)/Contents/MacOS/monomi
	cp launch.sh $(APP_DIR)/Contents/MacOS
	chmod a+x $(APP_DIR)/Contents/MacOS/launch.sh
	mkdir $(APP_DIR)/Contents/Resources
	cp -r ../../assets/* $(APP_DIR)/Contents/Resources
	mkdir $(APP_DIR)/Contents/Frameworks
	cp ../../ext/sdl/lib/libSDL.dylib $(APP_DIR)/Contents/Frameworks
	install_name_tool -id $(SDL_INSTALL_NAME) $(APP_DIR)/Contents/Frameworks/libSDL.dylib
	touch app.made

run: app.made
	open $(APP_DIR)

clean:
	rm -fr $(APP_DIR) *.made

.PHONY: all clean run

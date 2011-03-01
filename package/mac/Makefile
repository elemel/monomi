APP_DIR := Monomi.app

all: app.made

app.made:
	rm -fr $(APP_DIR)
	mkdir $(APP_DIR)
	mkdir $(APP_DIR)/Contents
	cp Info.plist $(APP_DIR)/Contents
	mkdir $(APP_DIR)/Contents/MacOS
	cp ../../src/monomi $(APP_DIR)/Contents/MacOS
	mkdir $(APP_DIR)/Contents/Resources
	mkdir $(APP_DIR)/Contents/Frameworks
	cp ../../ext/sdl/lib/libSDL.dylib $(APP_DIR)/Contents/Frameworks
	install_name_tool -id @executable_path/../Frameworks/libSDL.dylib $(APP_DIR)/Contents/Frameworks/libSDL.dylib
	touch app.made

clean:
	rm -fr $(APP_DIR) *.made

.PHONY: all clean

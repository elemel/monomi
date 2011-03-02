RAPIDXML_EXT_DIR := ../..
RAPIDXML_INCLUDE_DIR := $(RAPIDXML_EXT_DIR)/include
RAPIDXML_SRC_DIR := $(RAPIDXML_EXT_DIR)/src

all: include.made

include.made:
	rm -fr $(RAPIDXML_INCLUDE_DIR)
	mkdir $(RAPIDXML_INCLUDE_DIR)
	cp $(RAPIDXML_SRC_DIR)/*.hpp $(RAPIDXML_INCLUDE_DIR)
	touch include.made

clean:
	rm *.made

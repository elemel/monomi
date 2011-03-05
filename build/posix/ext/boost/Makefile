BOOST_EXT_DIR := ../../../../ext/boost-1.46.0
BOOST_INCLUDE_DIR := $(BOOST_EXT_DIR)/include
BOOST_SRC_DIR := $(BOOST_EXT_DIR)/src

all: include.made

include.made:
	rm -fr $(BOOST_INCLUDE_DIR)
	mkdir $(BOOST_INCLUDE_DIR)
	cp -r $(BOOST_SRC_DIR)/boost $(BOOST_INCLUDE_DIR)
	touch include.made

clean:
	rm *.made

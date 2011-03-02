all:
	cd ext && make
	cd release && make
	cd package/mac && make

run: all
	cd package/mac && make run

.PHONY: all run

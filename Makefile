all:
	cd ext && make
	cd build/posix/release && make depend && make
	cd package/mac && make clean && make

run: all
	cd package/mac && make run

clean:
	cd package/mac && make clean
	cd build/posix && make clean
	cd ext && make clean

.PHONY: all clean run

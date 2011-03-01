all:
	cd ext && make
	cd build/posix/release && make
	cd package/mac && make clean && make

clean:
	cd package/mac && make clean
	cd build/posix/release && make clean
	cd ext && make clean

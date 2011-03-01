install.made: build.made
	rm -fr include lib
	mkdir -p include/glog lib
	cp src/src/glog/*.h include/glog
	cp src/.libs/libglog.a lib
	touch install.made

build.made: extract.made
	cd src && ./configure && make
	touch build.made

extract.made: download.made
	rm -fr src
	mkdir src
	tar xzf src.tar.gz -C src --strip-components 1
	touch extract.made

download.made:
	rm -fr src.tar.gz
	wget -O src.tar.gz http://google-glog.googlecode.com/files/glog-0.3.1-1.tar.gz
	touch download.made

clean:
	rm -fr src src.tar.gz *.made

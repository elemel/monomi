install.made: extract.made
	rm -fr include
	mkdir include
	cp -r src/boost include
	touch install.made

extract.made: download.made
	rm -fr src
	mkdir src
	tar xzf src.tar.gz -C src --strip-components 1
	touch extract.made

download.made:
	rm -fr src.tar.gz
	wget -O src.tar.gz http://sourceforge.net/projects/boost/files/boost/1.45.0/boost_1_45_0.tar.gz/download
	touch download.made

clean:
	rm -fr src src.tar.gz *.made

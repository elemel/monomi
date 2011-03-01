package.made: src.made
	cd package/mac && make
	touch package.made

src.made: ext.made
	cd src && make
	touch src.made

ext.made:
	cd ext && make
	touch ext.made
    
clean:
	rm -fr *.made

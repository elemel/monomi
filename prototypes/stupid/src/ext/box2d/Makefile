install.made: build.made
	rm -fr include lib
	mkdir include lib
	( cd src/Box2D && tar -cf - `find Box2D -name "*.h" -print` ) | ( cd include && tar xBf - )
	cp src/Box2D/Box2D/libBox2D.a lib
	touch install.made

build.made: checkout.made
	cd src/Box2D && cmake -G "Unix Makefiles" && make Box2D
	touch build.made

checkout.made:
	rm -fr src
	svn checkout http://box2d.googlecode.com/svn/trunk/ src
	touch checkout.made

clean:
	rm -fr src *.made

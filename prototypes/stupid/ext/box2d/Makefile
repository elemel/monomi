dist.made: build.made
	rm -fr include lib
	mkdir include lib
	( cd src/Box2D && tar -cf - `find Box2D -name "*.h" -print` ) | ( cd include && tar xBf - )
	cp src/Box2D/Box2D/libBox2D.a lib
	touch dist.made

build.made: src.made
	cd src/Box2D && cmake -G "Unix Makefiles" && make Box2D
	touch build.made

src.made:
	rm -fr src
	svn checkout http://box2d.googlecode.com/svn/trunk/ src
	touch src.made

clean:
	rm -fr src *.made

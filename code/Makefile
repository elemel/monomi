CXXFLAGS := -I/opt/local/include -I/usr/local/include/SDL -framework OpenGL -lSDL

monomi: *.cpp *.hpp
	g++ -o monomi *.cpp $(CXXFLAGS)

clean:
	rm -f monomi

CXXFLAGS += -Wall -Wextra -std=c++14 -Weffc++

top-vect: main.cpp
	g++ -o $@ $^

clean:
	rm -rf *.o top-vect
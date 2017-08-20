# Written by Stephan Kreutzer, 2017.
# This file is contributed to the public domain (Gemeinfreiheit).

.PHONY: build prepare clean

build: nante



nante: nante.cpp
	g++ nante.cpp -lncurses -lpanel -o nante

prepare:
	sudo apt-get install libncurses-dev

clean:
	rm -f ./nante

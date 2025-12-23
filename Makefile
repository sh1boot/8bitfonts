CXX=clang++
CXXFLAGS=-std=c++20 -pedantic -Werror -Wall
all: 8bitfont

run: 8bitfont
	./$^ -i c64.bin

clean:
	rm -f 8bitfont *.tlf

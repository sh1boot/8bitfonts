CXXFLAGS=-std=c++20 -pedantic -Werror -Wall
all: 8bitfont

run: 8bitfont
	./$^ petscii.txt < c64.bin

clean:
	rm -f 8bitfont


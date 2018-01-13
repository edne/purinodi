lib.name = purinodi
class.sources = src/pn_view.cpp src/pn_square.cpp src/pn_scale.cpp src/pn_polygon.cpp
shared.sources = src/global.cpp

CXX = g++
cflags = -O2 -Wall -Wextra -Isrc -std=c++0x
ldlibs = -lglfw -lGL -lm

include Makefile.pdlibbuilder


test:
	make clean && make && sudo make install && pd test.pd


.PHONY: test

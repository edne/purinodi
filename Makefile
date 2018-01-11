lib.name = ggdG
class.sources = src/gg_view.cpp src/gg_square.cpp src/gg_scale.cpp src/gg_polygon.cpp
shared.sources = src/global.cpp

CXX = g++
cflags = -O2 -Wall -Wextra -Isrc -std=c++0x
ldlibs = -lglfw -lGL -lm

include Makefile.pdlibbuilder


test:
	make clean && make && sudo make install && pd test.pd


.PHONY: test

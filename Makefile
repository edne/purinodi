lib.name = ggdG
class.sources = src/gg_foo.cpp

CC = g++
cflags = -std=c++11 -O2 -Wall -Wextra -Isrc
ldlibs = -lglfw -lGL -lm

include Makefile.pdlibbuilder


test:
	make clean && make && sudo make install && pd test.pd


.PHONY: test

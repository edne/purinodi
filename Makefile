lib.name = ggdG
class.sources = src/gg_foo.cpp src/gg_source.cpp src/gg_sink.cpp src/gg_proxy.cpp
shared.sources = src/global.cpp

CXX = g++
cflags = -O2 -Wall -Wextra -Isrc -std=c++0x
ldlibs = -lglfw -lGL -lm

include Makefile.pdlibbuilder


test:
	make clean && make && sudo make install && pd test.pd


.PHONY: test

.DEFAULT_GOAL := test

.PHONY: test clean

CC = g++


clean:
	rm build/*

test: build/timer_test
	build/timer_test

build/timer_test: timer_test.cpp timer.hpp
	[[ -e build ]] || mkdir build
	$(CC) -o $@ timer_test.cpp

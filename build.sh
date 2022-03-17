#!/bin/sh
cmake --build ./build
if [ $? -eq 0 ];then
	clear
	./build/sdl
fi

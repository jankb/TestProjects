
all: build/pwm

.PHONY: all

build/pwm: build/gpio.o main.cpp | builddir
	g++ $^ -o $@

build/gpio.o: gpio.cpp gpio.h | builddir
	g++ -I. -c gpio.cpp -o $@

builddir:
	mkdir -p build

clean:
	rm -rf ./build

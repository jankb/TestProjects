
all: build/pwm

.PHONY: all

build/pwm: build/gpio.o build/pwm.o main.cpp | builddir
	g++ $^ -o $@ -lpthread

build/gpio.o: gpio.cpp gpio.h | builddir
	g++ -I. -c gpio.cpp -o $@

build/pwm.o: pwm.cpp pwm.h | builddir
	g++ -I. -c pwm.cpp -o $@

builddir:
	mkdir -p build

clean:
	rm -rf ./build

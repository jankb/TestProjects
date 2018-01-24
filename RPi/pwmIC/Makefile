
all: pwm

pwm: builddir gpio.o  
	g++ main.cpp ./build/gpio.o -o ./build/pwm

gpio.o: gpio.cpp gpio.h
	g++ -I. -c gpio.cpp -o ./build/gpio.o

builddir:
	mkdir -p build

clean:
	rm -rf ./build

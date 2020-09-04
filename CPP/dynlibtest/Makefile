
app: app.cpp libtestlib.so 
	g++ -o app app.cpp -ldl

libtestlib.so: testlib.cpp
	g++ -shared -o libtestlib.so testlib.cpp


all: app 

clean:
	rm libtestlib.so app


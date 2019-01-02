main:
	g++ -o 4 4.cpp `pkg-config --cflags --libs opencv`
	
run:
	./4

clean:
	rm 4
	

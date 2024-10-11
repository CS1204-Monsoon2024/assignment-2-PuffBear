default: main.out

main.out: main.cpp
	g++ -std=c++11 main.cpp -o main.out

run: main.out
	./main.out

clean:
	rm -f main.out
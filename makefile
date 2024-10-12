default:
	g++ -std=c++11 main.cpp -o ./main.out
	chmod +x ./main.out  # Ensure the output file is executable

run: main.out
	./main.out

clean:
	rm -f main.out
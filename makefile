default:
	g++ -std=c++11 main.cpp HashTable.cpp -o resulting && ./main.out

clean:
	rm *.out

default:
	g++ -std=c++11 main.cpp HashTable.cpp -o resulting && ./resulting

clean:
	rm *.out

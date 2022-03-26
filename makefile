main:
	g++ -o main main.cpp -std=c++11 -I /usr/local/include/rocketmq/ -L /usr/local/lib -lrocketmq
clean:
	rm -f main
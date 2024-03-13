build:
	@g++ -o ./bin/main main.cpp -std=c++17
run: build
	@./bin/main

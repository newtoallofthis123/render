build:
	@g++ -o ./bin/main main.cpp -std=c++20
run: build
	@./bin/main

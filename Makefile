build:
	@g++ -o ./bin/render main.cpp -std=c++20
run: build
	@./bin/render
clean:
	@rm -rf ./bin/render
	@echo "Cleaned up the build files"
client_build:
	@g++ -o ./bin/client client.cpp -std=c++20
client_run: client_build
	@./bin/client

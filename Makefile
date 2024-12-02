default:
	clear
	g++ -o falling_sand main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./falling_sand

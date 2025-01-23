all: main.cpp screen.cpp player.cpp obstacle_generator.cpp obstacle.cpp
	g++ -g main.cpp screen.cpp player.cpp obstacle_generator.cpp obstacle.cpp -lX11 -lncurses -o m
	

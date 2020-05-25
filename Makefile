default:
	g++ server.cpp Game.cpp -o server -lsfml-graphics -lsfml-window -lsfml-system
	g++ client.cpp Game.cpp -o client -lsfml-graphics -lsfml-window -lsfml-system
	g++ main.cpp -o window -lsfml-graphics -lsfml-window -lsfml-system
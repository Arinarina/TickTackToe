default:
	g++ server.cpp Game.cpp -o server
	g++ client.cpp Game.cpp -o client
	g++ main.cpp -o window -lsfml-graphics -lsfml-window -lsfml-system
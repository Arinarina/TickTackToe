default:
	g++ server.cpp Game.cpp -o server
	g++ client.cpp Game.cpp -o client
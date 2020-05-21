#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include "Game.h"

using namespace std;

#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	// создаем сокет
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 
	// подоключаемся к серверу
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	// получаем размер поля
	int fieldBuffer[1] = {0};
	valread = recv(sock , fieldBuffer, 1, 0); 
	cout << "The field size is " << fieldBuffer[0];
	int sizes = fieldBuffer[0];
	// создаем обьект класса игры
    Game *game = new Game(sizes);

	int myBuffer[2] = {0, 0};
	int x, y;
	int move = 0;
    int turn = game->first;
	game->showInstruction();
	// игровой цикл
	while (!game->rowCrossed() && !game->columnCrossed() && !game->diagonalCrossed() && move != sizes*sizes) { 
        cout << "Waiting...." << endl;
		// ждем пока придет ход соперника
		valread = recv(sock, myBuffer, sizeof(int) * 2, 0);
        cout << "Recived" << myBuffer[0] << " " << myBuffer[1] << endl;
		// создаем новый ход, заполняем клетку поля, показываем само поле
		int status = game->newMove(game->first, move, myBuffer[0], myBuffer[1]);
        if (status == -1)
            break;
        move++;
        game->showBoard();
		// проверяем на победителя
		int gameEnd = game->checkWin(move, game->second);
        if (gameEnd) // если есть победитель, заканчиваем игру
            break;
		// вводим координаты для хода
		cout << "Enter x, y" << endl;
		cin >> x >> y;

		myBuffer[0] = x;
		myBuffer[1] = y;

		cout << "--------------" << endl;
		// создаем ход, показываем поле
		status = game->newMove(game->second, move, x, y);
        if (status == -1)
            break;
        move++;
        game->showBoard();
		// отправляем ход клиента на сервер
		send(sock, myBuffer, sizeof(int) * 2, 0);
		// проверяем на победителя
		gameEnd = game->checkWin(move, game->first);
        if (gameEnd)
            break;
	}

	return 0; 
} 

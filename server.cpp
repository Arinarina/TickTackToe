#include <SFML/Graphics.hpp>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <iostream>
#include <string.h>
#include <functional>

#include "Game.h"

#define PORT 8080 

// default field value
int sizes = 5;
#define DISP_WIDTH 320
#define DISP_FULL_HEIGHT 400

using namespace std;

int main(int argc, char const *argv[]) 
{ 
    // сокет клиента
    int sockets[2];

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    // настраиваем сервер
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 
    
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    // ждем подключение клиента
    if ((new_socket = accept(server_fd, (struct sockaddr *) & address,  (socklen_t*) &addrlen)) < 0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    cout << "Client connected! Socket -  " << new_socket << endl;
    cout << "Enter field sizes ( > 5)" << endl;
    int sizes;
    cin >> sizes;

    sf::RenderWindow window(sf::VideoMode(DISP_WIDTH, DISP_FULL_HEIGHT), "Tick Tack Toe");
    window.clear(sf::Color::Black);

    // задаем размеры игрового поля
    cout << "Field sizes is " << sizes << endl;
    // создаем игру
    Game *game = new Game(sizes);
    game->setRenderWindow(&window);

    sf::Thread thread(std::bind(Game::checkDisplayClosed, &window), &game);
    thread.launch();

    game->renderGameField();
    
    // отсылаем клиенту размеры игрового поля
    int littleBuffer[1] = { sizes };
    send(new_socket , littleBuffer, 1, 0); 
    
    int x, y;
    // буффер для пересылки хода клиенту
    int myBuffer[2] = {0, 0};

    int move = 0;
    // устаанавливаем ход игры
    int turn = game->first;
    // показываем инструкцию и поле
    game->showInstruction();
    game->showBoard();
    // игровой цикл
    while (!(game->rowCrossed()) && !(game->columnCrossed()) && !(game->diagonalCrossed()) && move != sizes*sizes) {
        // первым ходит сервер
        cout << "Enter x,y: ";
        cin >> x >> y;
        myBuffer[0] = x;
        myBuffer[1] = y;
        // создаем новых ход
        int status = game->newMove(game->first, move, x, y);
        if (status == -1)
            break;
        move++;
        game->showBoard();
        // показываем ход на поле
        // отправляем ход клиенту
        send(new_socket , myBuffer, sizeof(int) * 2, 0); 
        cout << "Waiting...." << endl;
        // проверяем на победителя
        int gameEnd = game->checkWin(move, game->second);
        if (gameEnd)
            break;
        // ждем хода соперника
		valread = recv(new_socket, myBuffer, sizeof(int) * 2, 0);
        cout << "Recived" << myBuffer[0] << " " << myBuffer[1] << endl;
		// отмечаем ход соперника на поле
        status = game->newMove(game->second, move, myBuffer[0], myBuffer[1]);
        if (status == -1)
            break;
        move++;
        // показываем поле
        game->showBoard();
        // проверка на победителя
        gameEnd = game->checkWin(move, game->first);
        if (gameEnd)
            break;
    }

    
    return 0; 
} 
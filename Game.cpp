#include <iostream>
#include "Game.h"

using namespace std;

// конструктор без парааметров
Game::Game() {
    first = 1;
    second = 2;
    firstMove = 'O';
    secondMove = 'X';
    cout << "Enter side value" << endl;
    cin >> side;
    this->board = new char*[side];
    for (int i = 0; i< side; i++) {
        this->board[i] = new char[side];
    }
    this->moves = new int[side*side]; 
    
    for (int i=0; i<side; i++) 
    { 
        for (int j=0; j<side; j++) 
            this->board[i][j] = ' '; 
    } 
    for (int i=0; i<side*side; i++) 
        this->moves[i] = i; 
}
// конструктор с параметрами, введены раазмеры поля
Game::Game(int side) {
    this->side = side;
    first = 1;
    second = 2;
    firstMove = 'O';
    secondMove = 'X';
    this->board = new char*[side];
    for (int i = 0; i< side; i++) {
        this->board[i] = new char[side];
    }
    this->moves = new int[side*side]; 
    
    for (int i=0; i<side; i++) 
    { 
        for (int j=0; j<side; j++) 
            board[i][j] = '_'; 
    } 
    for (int i=0; i<side*side; i++) 
        moves[i] = i; 
    
}

// деструктор
Game::~Game() {
    first = 0;
    second = 0;
    side = 0;
    for (int i = 0; i< side; i++) {
        delete this->board[i];
    }
    delete[] board;
    delete[] moves;
}

void Game::setRenderWindow(sf::RenderWindow *window) {
    this->window = window;
}

void Game::renderGameField() {
    for (int i = 1; i <= side; i++) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i * (DISP_WIDTH / side), 0)),
            sf::Vertex(sf::Vector2f(i * (DISP_WIDTH / side), 320))
        };
        (*window).draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(0, i * (DISP_WIDTH / side)));
        line[1] = sf::Vertex(sf::Vector2f(320, i * (DISP_WIDTH / side)));
        (*window).draw(line, 2, sf::Lines);
    }
    // will be rendered on next tick
}

void Game::checkDisplayClosed(sf::RenderWindow *window) {
    (*window).clear(sf::Color::Black);
    while ((*window).isOpen())
    {
        sf::Event event;
        while ((*window).pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                (*window).close();
        }

        (*window).display();
    }
}

// показываем инструкции
void Game::showInstruction() 
{ 
    cout << endl << "Choose the field" << endl;
      
    for (int i = 0 ; i < side; i++) {
        for (int j = 0; j < side; j++) {
            cout << "| " << i << "/" << j << " |";
        }
        cout << endl;
        for (int j = 0; j < side; j++)
            cout << "-------";
        cout << endl;
    }
  
    return; 
} 

// показываем игровое поле
void Game::showBoard() 
{ 
    cout << endl;
    cout << side << endl;
    for (int i = 0 ; i < side; i++) {
        for (int j = 0; j < side; j++) {
            cout << "| " << board[i][j] << " |";
        }
        cout << endl;
        for (int j = 0; j < side; j++)
            cout << "-----";
        cout << endl;
    }
    return; 
} 

// 5 в один столбец
bool Game::rowCrossed() 
{ 
    int xx, yy;
    int starting = 0;
    for (int i = 0; i < side; i++) 
    { 
        while (starting + 4 < side) {
            xx = 0;
            yy = 0;
            for (int j = starting; j < starting + 5; j++) {
                // cout << j << " " << i << endl;;
                if (board[i][j] == 'O') {
                    xx++;
                }
                if (board[i][j] == 'X') {
                    yy++;
                }
            }
            if (xx >= 5) {
                return true;
            }
            if (yy >= 5) {
                return true;
            }
            starting++;
        }
    } 
    return(false); 
} 

// 5 в одну колонку
bool Game::columnCrossed() 
{ 
    int xx, yy;
    int starting = 0;
    for (int j = 0; j < side; j++) 
    { 
        while (starting + 4 < side) {
            xx = 0;
            yy = 0;
            for (int i = starting; i < starting + 5; i++) {
                if (board[i][j] == 'O') {
                    xx++;
                }
                if (board[i][j] == 'X') {
                    yy++;
                }
            }
            if (xx >= 5) {
                return true;
            }
            if (yy >= 5) {
                return true;
            }
            starting++;
        }
    } 
    return(false); 
} 

// 5 по диагонали
bool Game::diagonalCrossed() 
{ 
    // проверка диагоналей основной и обратной
    int xx, yy;
    int starting = 0;
    xx = 0;
    yy = 0;
    for (int i = 0; i < side; i++) {
        if (board[i][i] == 'O') {
            xx++;
        }
        if (board[i][i] == 'X') {
            yy++;
        }
        if (board[i][i] == '_') {
            xx = 0;
            yy = 0;
        }
        if ((xx == 5) || (yy == 5)) {
            return true;
        }
    }
    // обратная диагональ
    xx = 0;
    yy = 0;
    for (int i = 0; i < side; i++) {
        if (board[side - 1 - i][side - 1 - i] == 'O') {
            xx++;
        }
        if (board[side - 1 - i][side - 1 - i] == 'X') {
            yy++;
        }
        if (board[side - 1 - i][side - 1 - i] == '_') {
            xx = 0;
            yy = 0;
        }
        if ((xx == 5) || (yy == 5)) {
            return true;
        }
    }
    // побочные диагонали по наравлению главной
    int preX = 1;
    for (int i = 1; i <= side - 5; i++) {
        xx = 0;
        yy = 0;
        for (int j = 0; j < side - i; j++) {
            if (board[preX + j][j] == 'O') {
                xx++;
                yy = 0;
            }
            if (board[preX + j][j] == 'X') {
                yy++;
                xx = 0;
            }
            if (board[preX + j][j] == '_') {
                yy = 0;
                xx = 0;
            }

            if ((xx == 5) || (yy == 5)) {
                return true;
            }
        }

        preX++;
    }

    preX = 1;
    for (int i = 1; i <= side - 5; i++) {
        xx = 0;
        yy = 0;
        for (int j = 0; j < side - i; j++) {
            if (board[j][preX + j] == 'O') {
                xx++;
                yy = 0;
            }
            if (board[j][preX + j] == 'X') {
                yy++;
                xx = 0;
            }
            if (board[j][preX + j] == '_') {
                yy = 0;
                xx = 0;
            }

            if ((xx == 5) || (yy == 5)) {
                return true;
            }
        }

        preX++;
    }
    // Побочные диагонали
    preX = 1;
    for (int i = 1; i <= side - 5; i++) {
        xx = 0;
        yy = 0;
        for (int j = 0; j < side - i; j++) {
            if (board[side - 1 - (preX + j)][side - 1 - j] == 'O') {
                xx++;
                yy = 0;
            }
            if (board[side - 1 - (preX + j)][side - 1 - j] == 'X') {
                yy++;
                xx = 0;
            }
            if (board[side - 1 - (preX + j)][side - 1 - j] == '_') {
                yy = 0;
                xx = 0;
            }

            if ((xx == 5) || (yy == 5)) {
                return true;
            }
        }

        preX++;
    }

    preX = 1;
    for (int i = 1; i <= side - 5; i++) {
        xx = 0;
        yy = 0;
        for (int j = 0; j < side - i; j++) {
            if (board[side - 1 - j][side - 1 - (preX + j)] == 'O') {
                xx++;
                yy = 0;
            }
            if (board[side - 1 - j][side - 1 - (preX + j)] == 'X') {
                yy++;
                xx = 0;
            }
            if (board[side - 1 - j][side - 1 - (preX + j)] == '_') {
                yy = 0;
                xx = 0;
            }

            if ((xx == 5) || (yy == 5)) {
                return true;
            }
        }

        preX++;
    }


    return false;
} 

// новый ход в игре (считываем куда ходим, устанавливаем на доску)
int Game::newMove(int turn, int move, int x, int y){
    char currentSym;
    if (turn == first) 
        currentSym = firstMove; 
    else if (turn == second) 
        currentSym = secondMove; 

    if (x > side - 1 || y > side - 1) {
        cout << "Field out of range" << endl;
        return -1;
    }
            
    if (board[x][y] != '_'){
        cout << "Field is bisy" << endl;
        return -1;
    }
    cout << x << " " << y << endl;
         
    board[x][y] = currentSym; 
         
    cout << board[x][y] << " in " << moves[move] / side << " " << moves[move] %side << endl;
    showBoard();
    return 0;
}

// Проверяем победителя по всем правилам
int Game::checkWin(int move, int turn){
    if (move == side * side) {
        printf("No winner\n"); 
        return 1;
    }
    else if (rowCrossed() || columnCrossed() || diagonalCrossed())
    { 
        if (turn == first) 
            printf("second win\n"); 
        else
            printf("first win\n"); 
        return 1;
    }
    else
        return 0;
}
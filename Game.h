#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

#define DISP_WIDTH 320
#define DISP_FULL_HEIGHT 400

class Game
{
private:
    int side;
    char** board;
    int *moves;
    sf::RenderWindow *window;
 
public:
    Game();
    Game(int side);
    ~Game();
    int first, second;
    char firstMove, secondMove;
 
    void showBoard();
    void showInstruction();
    bool rowCrossed();
    bool columnCrossed();
    bool diagonalCrossed();
    int checkWin(int move, int turn);
    int newMove(int turn, int move, int x, int y);

    void setRenderWindow(sf::RenderWindow *window);
    void renderGameField();
    void drawTick(int x, int y);
    void drawRound(int x, int y);

    void drawInfo(int state);
    void clearText();
    void drawWinnerText(string winner);

    // static functions
    static void checkDisplayClosed(sf::RenderWindow *window);
};
 
#endif // GAME_H
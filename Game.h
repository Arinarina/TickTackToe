#ifndef GAME_H
#define GAME_H
 
class Game
{
private:
    int side;
    char** board;
    int *moves;
 
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
};
 
#endif // GAME_H
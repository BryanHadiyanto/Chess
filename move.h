#ifndef MOVE_H
#define MOVE_H
#include <iostream>
using namespace std;
#include <piece.h>

class Move
{
private:
    int x1, y1, x2, y2;
    Player player;
    string ** field;
    bool isPawnMoveValid();
    bool isRookMoveValid();
    bool isKnightMoveValid();
    bool isBishopMoveValid();
    bool isQueenMoveValid();
    bool isKingMoveValid();
    bool isDiagonalMoveValid();
    bool isPerpendicularMoveValid();
    bool isFigureOwnedByPlayer(string figure);
public:
    Move(int x1,int y1,int x2,int y2, Player * player, string **field){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->player = *player;
        this->field = field;
    };
    bool isValid();
    void doesBeatFigure();
    void executeMove();
};

#endif // MOVE_H

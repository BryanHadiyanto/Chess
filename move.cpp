#include "move.h"

bool Move::isFigureOwnedByPlayer(string figure){
    return (figure.at(0) == 'w' && player == white) || (figure.at(0) == 's' && player == black);
}

bool Move::isDiagonalMoveValid(){
    if(isFigureOwnedByPlayer(field[x2][y2])){
        return false;
    }else if (abs(x1 - x2) == abs(y1 - y2))
    {
        int xIncrement = (x2 - x1) / (abs(x2 - x1));
        int yIncrement = (y2 - y1) / (abs(y2 - y1));

        for (int i = 1; i < abs(x1 - x2); i++)
        {
            if (field[x1 + xIncrement*i][y1 + yIncrement*i] != "__"){
                return false;
            }

        }
        return true;
    }else {
        return false;
    }
}

bool Move::isPerpendicularMoveValid(){
    if(x1 != x2 && y1 != y2){
        return false;
    }else if(isFigureOwnedByPlayer(field[x2][y2])) {
        return false;
    }
    else {
        if(y1 == y2){
            int xDirection = (x2 - x1) / (abs(x2 - x1));
            for(int i = x1 + xDirection; i != x2; i+=xDirection){
                if(field[i][y1] != "__"){
                    return false;
                }
            }
        }else if(x1 == x2) {
            int yDirection = (y2 - y1) / (abs(y2 - y1));
            for(int i = y1 + yDirection; i != y2; i+=yDirection){
                if(field[x1][i] != "__"){
                    return false;
                }
            }
        }else {
            cout << "Something went wrong" << endl;
            return false;
        }
        return true;
    }
}

bool Move::isPawnMoveValid(){
    if(abs(x2 - x1) > 2 || abs(y2 - y1) > 1) {
        cout << "Sowit kann ein Bauer nicht laufen!" << endl;
        return false;
    }else if(abs(x2-x1) == 1 && abs(y2-y1) == 1){
        if(isFigureOwnedByPlayer(field[x2][y2]) || field[x2][y2] == e){
            cout << "Ein Bauer kann diagonal nur angreifen." << endl;
            return false;
        }else {
            return true;
        }
    }else if(y1 == y2){
        if(player == black && x2 - x1 < 0){
            if(abs(x2 - x1) == 2){
                if(x1 != 6){
                    return false;
                }else {
                    if(field[x1-1][y1] != e || field[x1-2][y1] != e){
                        cout << "Der Weg ist blockiert!" << endl;
                        return false;
                    }else {
                        return true;
                    }
                }
            }else {
                if(field[x2][y2] != e){
                    cout << "Der Weg ist blockiert!" << endl;
                    return false;
                }else {
                    return true;
                }
            }
        }else if(player == white && x2 - x1 > 0){
            if(abs(x2 - x1) == 2){
                if(x1 != 1){
                    return false;
                }else {
                    if(field[x1+1][y1] != e || field[x1+2][y1] != e){
                        cout << "Der Weg ist blockiert!" << endl;
                        return false;
                    }else {
                        return true;
                    }
                }
            }else {
                if(field[x2][y2] != e){
                    cout << "Der Weg ist blockiert!" << endl;
                    return false;
                }else {
                    return true;
                }
            }
        }
        else {
            return false;
        }
    }
    return false;
}

bool Move::isRookMoveValid(){
    return isPerpendicularMoveValid();
}

bool Move::isKnightMoveValid(){
    if(isFigureOwnedByPlayer(field[x2][y2])){
        cout << "Das Ziel ist blockiert!" << endl;
        return false;
    }
    if ((abs(x1 - x2) == 2 && abs(y1 - y2) == 1) || (abs(x1 - x2) == 1 && abs(y1 - y2) == 2)){
        return true;
    }else {
        cout << "So kann sich ein Springer nicht bewegen!" << endl;
        return false;
    }
    return false;
}

bool Move::isBishopMoveValid(){
    return isDiagonalMoveValid();
}

bool Move::isQueenMoveValid(){
    return isDiagonalMoveValid() || isPerpendicularMoveValid();
}

bool Move::isKingMoveValid(){
    if(abs(x2-x1) > 1 || abs(y2-y1) > 1){
        cout << "König kann nur 1 Schritt in jede richtung laufen!" << endl;
        return false;
    }else {
        if(isFigureOwnedByPlayer(field[x2][y2])){
            cout << "Der Weg ist blockiert!" << endl;
            return false;
        }else {
            return true;
        }
    }
}

bool Move::isValid()
{
    if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7){
        cout << "Die Koordinaten müssen innerhalb des Spielfelds liegen!" << endl;
        return false;
    }

    if(x1 == x2 && y1 == y2){
        cout << "Die Figur muss sich um mindestens ein Feld bewegen." << endl;
        return false;
    }

    string figure = field[x1][y1];
    if(!isFigureOwnedByPlayer(figure)){
        cout << figure << "Falsche Spielfigur!" << endl;
        return false;
    }
    if(figure == wB || figure == sB) {
        return isPawnMoveValid();
    }else if(figure == wL || figure == sL) {
        return isBishopMoveValid( );
    }else if(figure == wS || figure == sS) {
        return isKnightMoveValid( );
    }else if(figure == wT || figure == sT) {
        return isRookMoveValid( );
    }else if(figure == wD || figure == sD) {
        return isQueenMoveValid( );
    }else if(figure == wK || figure == sK) {
        return isKingMoveValid( );
    }
    cout << "Sie müssen als Startpunkt eine Figur auswählen." << endl;
    return false;
}

void Move::doesBeatFigure() {
    if(!isFigureOwnedByPlayer(field[x2][y2]) && field[x2][y2] != e){
        cout << field[x2][y2] << " wurde geschlagen" << endl;
    }
}

void Move::executeMove() {
    field[x2][y2] = field[x1][y1];
    field[x1][y1] = e;
}

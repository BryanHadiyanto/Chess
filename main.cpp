#include <iostream>
using namespace std;
#include <move.h>
#include <piece.h>

void chessboard(string **board){
    cout << "  " << "a \t" << "b \t" << "c \t" << "d \t" << "e \t" << "f \t" << "g \t" << "h \t" << endl;
    for(int i = 7;i >= 0;i--){
        cout << i+1 << " ";
        for(int j = 0;j < 8;j++){
            cout << board[i][j] << "\t";
        }
        cout << endl;
        cout << " " << endl;
    }
}

bool isPositionAtRisk(int x, int y, string ** board) {
    char playerPrefix;
    char searchPrefix;
    if(board[x][y].at(0) == 's'){
        playerPrefix = 's';
        searchPrefix = 'w';
    }else {
        playerPrefix = 'w';
        searchPrefix = 's';
    }

    bool atRisk = false;

    // Search perpendicular - vertical
    for(int d: {-1, 1}){
        for(int i = x+d; i >= 0 && i < 8; i += d){
            if(board[i][y].at(0) == searchPrefix){
                if(abs(i-x) == 1 && board[i][y] == string(1, searchPrefix) + "K"){
                    atRisk = true;
                }else if(board[i][y] == string(1, searchPrefix) + "T" || board[i][y] == string(1, searchPrefix) + "D") {
                    atRisk = true;
                }
            }else if(board[i][y].at(0) == playerPrefix){
                break;
            }
        }
    }

    // Search perpendicular - horizontal
    for(int d: {-1, 1}){
        for(int i = y+d; i >= 0 && i < 8; i += d){
            if(board[x][i].at(0) == searchPrefix){
                if(abs(i-y) == 1 && board[x][i] == string(1, searchPrefix) + "K"){
                    atRisk = true;
                }else if(board[x][i] == string(1, searchPrefix) + "T" || board[x][i] == string(1, searchPrefix) + "D") {
                    atRisk = true;
                }
            }else if(board[x][i].at(0) == playerPrefix){
                break;
            }
        }
    }

    // Search diagonal - bottom left to top right
    // TODO Cleanup code
    for(int d: {-1, 1}){
        for(int i = 1; i >= 0 && i < 8; i++){
            int newX = x + d*i;
            int newY = y + d*i;
            if(newX < 8 && newX >= 0 && newY < 8 && newY >= 0){
                if(board[newX][newY].at(0) == searchPrefix){
                    if(board[newX][newY] == string(1, searchPrefix) + "L" || board[newX][newY] == string(1, searchPrefix) + "D") {
                        atRisk = true;
                    }else if(abs(newX-x) > 1 && board[newX][newY] == string(1, searchPrefix) + "K"){
                        atRisk = true;
                    }
                }else if(board[newX][newY].at(0) == playerPrefix){
                    break;
                }
            }
        }
    }

    // Search diagonal - top left to bottom right
    // TODO Cleanup code
    for(int d: {-1, 1}){
        for(int i = 1; i >= 0 && i < 8; i++){
            int newX = x + (-d)*i;
            int newY = y + d*i;
            if(newX < 8 && newX >= 0 && newY < 8 && newY >= 0){
                if(board[newX][newY].at(0) == searchPrefix){
                    if(board[newX][newY] == string(1, searchPrefix) + "L" || board[newX][newY] == string(1, searchPrefix) + "D") {
                        atRisk = true;
                    }else if(abs(newX-x) > 1 && board[newX][newY] == string(1, searchPrefix) + "K"){
                        atRisk = true;
                    }
                }else if(board[newX][newY].at(0) == playerPrefix){
                    break;
                }
            }
        }
    }

    // Search for Pawns
    if(playerPrefix == 's'){
        if(x-1 < 8 && x-1 >= 0 && y-1 < 8 && y-1 >= 0 && board[x-1][y-1] == wB ){
            atRisk = true;
        }
        if(x-1 < 8 && x-1 >= 0 && y+1 < 8 && y+1 >= 0 && board[x-1][y+1] == wB ){
            atRisk = true;
        }
    }else {
        if(x-1 < 8 && x-1 >= 0 && y-1 < 8 && y-1 >= 0 && board[x-1][y-1] == sB ){
            atRisk = true;
        }
        if(x-1 < 8 && x-1 >= 0 && y+1 < 8 && y+1 >= 0 && board[x-1][y+1] == sB ){
            atRisk = true;
        }
    }

    // Search for Knights
    for(int newX: {-2,2}){
        for(int newY: {-1, 1}){
            if(x+newX < 8 && x+newX >= 0 && y+newY < 8 && y+newY >= 0){
                if(playerPrefix == 's'){
                    if(board[x+newX][y+newY] == wS){
                        atRisk = true;
                    }
                }else {
                    if(board[x+newX][y+newY] == sS){
                        atRisk = true;
                    }
                }
            }
        }
    }

    // Search for Knights
    for(int newX: {-1,1}){
        for(int newY: {-2, 2}){
            if(x+newX < 8 && x+newX >= 0 && y+newY < 8 && y+newY >= 0){
                if(playerPrefix == 's'){
                    if(board[x+newX][y+newY] == wS){
                        atRisk = true;
                    }
                }else {
                    if(board[x+newX][y+newY] == sS){
                        atRisk = true;
                    }
                }
            }
        }
    }
    return atRisk;
}

void check(string ** board){
    for(int i = 0; i <8; i++){
        for(int j = 0; j <8; j++){
            if(board[i][j] == wK){
                if(isPositionAtRisk(i, j, board)){
                    cout << "Weißer König auf " << (char)(j+97) << i+1 << " steht im Schach" << endl;
                }
            }
            if(board[i][j] == sK){
                if(isPositionAtRisk(i, j, board)){
                    cout << "Schwarzer König auf " << (char)(j+97) << i+1 << " steht im Schach" << endl;
                }
            }
        }
    }
}

Move createMove(string command, Player *player, string **board) {
    int y1 = command[0] - 97;
    int x1 = command[1] - 49;
    int y2 = command[3] - 97;
    int x2 = command[4] - 49;
    Move m = Move(x1, y1, x2, y2, player, board);
    return m;
}

void switchPlayer(Player *player) {
    if(*player == black) {
        *player = white;
    }else {
        *player = black;
    }
}

int main()
{
    string **board = new string*[8];
    board[0] = new string[8]{wT, wS, wL, wK, wD, wL, wS, wT};
    board[1] = new string[8]{wB,wB,wB,wB,wB,wB,wB,wB};
    board[2] = new string[8]{e,e,e,e,e,e,e,e};
    board[3] = new string[8]{e,e,e,e,e,e,e,e};
    board[4] = new string[8]{e,e,e,e,e,e,e,e};
    board[5] = new string[8]{e,e,e,e,e,e,e,e};
    board[6] = new string[8]{sB,sB,sB,sB,sB,sB,sB,sB};
    board[7] = new string[8]{sT, sS, sL, sK, sD, sL, sS, sT};
    chessboard(board);

    // The player whos turn it is
    Player player = white;
    string input;
    bool exit = false;
    while(exit != true) {
        cout << (player == white ? "Weiß" : "Schwarz") << " ist an der Reihe!"  << endl;
        cout << "Bitte Zug eingeben (z.B. b1-c3)" << endl;
        cout << "(Zum abbrechen geben Sie 'exit' ein): ";
        cin >> input;
        if(input == "exit") {
            exit = true;
        }else{
            Move move = createMove(input, &player,board);
            if(move.isValid()) {
                move.doesBeatFigure();
                move.executeMove();
                chessboard(board);
                check(board);
                switchPlayer(&player);
            }else {
                cout << "Zug ungültig, bitt korrigieren!" << endl;
            }
        }
    }


    return 0;
}

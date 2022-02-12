// FourInARow3D.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

template<typename T>
struct BoardTemplate {
    T board[4][6][7];
};

typedef BoardTemplate<bool> Board;
typedef BoardTemplate<char> CharBoard;

template<typename T>
std::ostream& operator<<(std::ostream& os, const BoardTemplate<T>& board) {
    for(size_t layer = 0; layer < 4; layer++) {
        for(size_t y = 0; y < 6; y++) {
            for(size_t x = 0; x < 7; x++) {
                os << board.board[layer][5-y][x];
            }
            os << std::endl;
        }
        if(layer != 3) os << "=======";
        os << std::endl;
    }
    return os;
}

CharBoard receiveBoard(std::istream& is) {
    CharBoard result;

    for(size_t layer = 0; layer < 4; layer++) {
        for(size_t y = 0; y < 6; y++) {
            char line[100];
            is >> line;
            
            for(size_t x = 0; x < 7; x++) {
                result.board[layer][5-y][x] = line[x];
            }
        }
        std::string t;
        is >> t;
    }
    
    return result;
}

Board getPlayer(CharBoard b, char player) {
    Board result;

    for(size_t layer = 0; layer < 4; layer++) {
        for(size_t y = 0; y < 6; y++) {
            for(size_t x = 0; x < 7; x++) {
                result.board[layer][y][x] = (b.board[layer][y][x] == player);
            }
        }
    }
    return result;
}

bool isFourInARow(const Board& b, int x, int y, int layer, int dX, int dY, int dLayer) {
    for(int i = 0; i < 4; i++) {
        int newX = x + dX * i;
        int newY = y + dY * i;
        int newLayer = layer + dLayer * i;

        if(!(newX     >= 0 && newX     < 7 &&
             newY     >= 0 && newY     < 6 &&
             newLayer >= 0 && newLayer < 4)) {

            return false;
        }

        if(b.board[newLayer][newY][newX] == false) {
            return false;
        }
    }

    return true;
}

int countFourByFoursInDirection(const Board& b, int dX, int dY, int dLayer) {
    int totalCount = 0;

    for(size_t layer = 0; layer < 4; layer++) {
        for(size_t y = 0; y < 6; y++) {
            for(size_t x = 0; x < 7; x++) {
                if(isFourInARow(b, x, y, layer, dX, dY, dLayer)) {
                    totalCount++;
                    std::cout << "[====] x:" << x << " y:" << y << " layer:" << layer << std::endl;
                }
            }
        }
    }

    std::cout << "dX:" << dX << " dY:" << dY << " dL:" << dLayer << " >> " << totalCount << std::endl;
    return totalCount;
}

int countFourByFours(const Board& b) {
    int total = 0;

    total += countFourByFoursInDirection(b, 1, 0, 0);
    total += countFourByFoursInDirection(b, 0, 1, 0);
    total += countFourByFoursInDirection(b, 1, 1, 0);
    total += countFourByFoursInDirection(b,-1, 1, 0);

    total += countFourByFoursInDirection(b, 0, 0, 1);

    total += countFourByFoursInDirection(b, 1, 0, 1);
    total += countFourByFoursInDirection(b, 0, 1, 1);
    total += countFourByFoursInDirection(b, 1, 1, 1);
    total += countFourByFoursInDirection(b,-1, 1, 1);

    total += countFourByFoursInDirection(b, 1, 0, -1);
    total += countFourByFoursInDirection(b, 0, 1, -1);
    total += countFourByFoursInDirection(b, 1, 1, -1);
    total += countFourByFoursInDirection(b,-1, 1, -1);

    std::cout << "Total: " << total << std::endl;

    return total;
}

int main() {
    std::ifstream boardFile("board.txt");
    CharBoard board = receiveBoard(boardFile);
    std::cout << board;

    std::cout << std::endl;
    Board p1Board = getPlayer(board, '+');
    Board p2Board = getPlayer(board, '-');

    std::cout << "P1 Board: " << std::endl << p1Board;
    
    std::cout << "P1 Score: ";
    countFourByFours(p1Board);

    std::cout << "P2 Board: " << std::endl << p2Board;

    std::cout << "P2 Score: ";
    countFourByFours(p2Board);
}

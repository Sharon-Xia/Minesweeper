#ifndef BOARD_HPP
#define BOARD_HPP
#include "tile.hpp"
#include "tile_Bomb.hpp"
#include "Array2d.hpp"
#include "EndGameException.hpp"
#include <vector>


class Board
{
private:
void fillBoardWithTiles();

void incAdjacentTiles(int c, int r);

void revealAdjacentTiles(int c, int r);
public:

//
Board(int s, int nbs);

~Board();

int sizeOfBoard() const;
void reveal(int c, int r);
bool gameOver();

bool flag(int c, int r);
bool isFlagged(int c, int r);
int bombsLeft();

bool tileStatus(int c, int r);
void revealBombs();

std::string retrieveRow(int r);

private:
int size;
int nBombs;
Array2d* board; //pointer to array of rows
std::vector<Tile*> bombs;
int tilesLeft;
int numFlags;
};


#endif
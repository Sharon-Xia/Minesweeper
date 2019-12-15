#include "board.hpp"
#include "Array2d.hpp"
#include <cstdlib>

//for generating random numbers
#include <stdio.h> 
#include <stdlib.h> 
#include<time.h> 


Board::Board(int s, int nbs)
: size{s}, nBombs{nbs}, board{new Array2d{s, s}}, tilesLeft{s * s - nbs},
	numFlags{0}
{
	int bombsLeft = nbs;
	int r;
	int c;

	Board::fillBoardWithTiles();

	srand(time(0));
	while (bombsLeft > 0)
	{
		r = rand() % s;
		c = rand() % s;
		if ((*board)(c, r)->type() == "NORMAL")
		{
			delete (*board)(c, r);
			(*board)(c, r) = new Bomb();
			bombs.push_back((*board)(c,r));
			Board::incAdjacentTiles(c, r);
			--bombsLeft;
		}
	}
}



Board::~Board()
{
	delete board;
}


int Board::sizeOfBoard() const
{
	return size;
}


void Board::reveal(int c, int r) // if no adjacent, reveal patch
{
	if ((*board)(c, r)->type() == "BOMB")
	{
		throw EndGameException();
	}

	if ((*board)(c, r)->reveal()) //calls reveal, returns true if adj bombs = 0
	{
		revealAdjacentTiles(c, r);
	}
	--tilesLeft;
}


bool Board::gameOver()
{
	return tilesLeft <= 0;
}


bool Board::flag(int c, int r) // returns false if already revealed
{
	if ((*board)(c, r)->status()) //already revealed
	{
		return false;
	}
	else if ((*board)(c, r)->flagstatus()) // unflagging
	{
		(*board)(c, r)->flag();
		--numFlags;
		return true;
	}
	else //flagging
	{
		(*board)(c, r)->flag();
		++numFlags;
		return true;
	}
}


bool Board::isFlagged(int c, int r)
{
	return (*board)(c, r)->flagstatus();
}


int Board::bombsLeft()
{
	return nBombs - numFlags;
}


bool Board::tileStatus(int c, int r)
{
	return (*board)(c, r)->status();
}


void Board::revealBombs() 
{
	for (int i = 0; i < bombs.size(); ++i)
	{
		bombs[i]->reveal();
	}
}


std::string Board::retrieveRow(int r)
{
	std::string row = std::to_string(r) + " ";
	if (r < 10) // for alignment
	{
		row += " ";
	}

	int bombCount;
	for (int i = 0; i < Board::size; ++i)
	{
		Tile*& current = (*board)(i, r);
		bombCount = current->nearbyBombCount();
		if (current->status())
		{
			if (current->type() == "BOMB")
			{
				row += "  *";
			}
			else if (current->type() == "NORMAL" 
					and bombCount > 0)
			{
				row += "  " + std::to_string(bombCount);
			}
			else
			{
				row += "   ";
			}
		}
		else if (current->flagstatus())
		{
			row += "  #";
		}
		else
		{
			row += "  -";
		}
	}
	return row;
}



// *** PRIVATE METHODS *** 
void Board::fillBoardWithTiles()
{
	for(int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			(*board)(i, j) = new Tile();
			//all must be deallocated
		}
	}
}


void Board::incAdjacentTiles(int c, int r)
{
	//booEditLog("Current bomb: " + std::to_string(c) + ", " + std::to_string(r));
	for (int i = r-1; i <= r+1; ++i)
	{
		for (int j = c-1; j <= c+1; ++j)
		{
			if (i < size && j < size && i >=0 && j >= 0 && !(i == r && j == c)) //if within bounds
			{
				//booEditLog(std::to_string(j) + ", " + std::to_string(i));
				(*board)(j, i)->incBombCount();
			}
		}
	}
}

//should only be called on tiles with no adjacent bombs
void Board::revealAdjacentTiles(int c, int r) 
{
	for (int i = r-1; i <= r+1; ++i)
	{
		for (int j = c-1; j <= c+1; ++j)
		{
			if (i < size && j < size && i >=0 && j >= 0 && !(i == r && j == c) // if within bounds
				&& (*board)(j, i)->nearbyBombCount() == 0 
				&& (*board)(j, i)->status() != true) // if no adjacent bombs
			{
				//booEditLog(std::to_string(j) + ", " + std::to_string(i));
				Board::reveal(j, i);
			}
		}
	}
}
#include "Game.hpp"

void displayBoard(Board* game)
{
	// first line
	std::cout << "   ";
	for (int i = 0; i < game->sizeOfBoard(); ++i)
	{
		if (i < 10) // for alignment
		{
			std::cout << " ";
		}
		std::cout << " " << i ;
	}
	std::cout << std::endl;

	// subsequent lines
	for (int i = 0; i < game->sizeOfBoard(); ++i)
	{
		std::cout << game->retrieveRow(i) << std::endl;
	}
}

bool startGame(Board* game) //win game/lose game
{
	// little game intro
	std::cout << ">> Game Started <<" << std::endl;
	std::cout << ">> Remember '# x y' is for flagging bombs" << std::endl;
	std::cout << ">> Game ends when all non-bomb tiles are revealed" << std::endl;
	std::cout << std::endl;


	int c;
	int r;
	std::string buffer; //for collecting extra

	try
	{
		while(true)
		{
			std::cout << "Enter Coordinates (x, y) in '- x y' format >> ";
			std::cin >> buffer >> c >> r;
			//std::getline(std::cin, buffer);
			if (buffer == "-")
			{
				if (game->tileStatus(c, r))
				{
					std::cout << ">> Already Revealed <<" << std::endl;
				}
				else
				{
					game->reveal(c, r);
				}
				displayBoard(game);

				if (game->gameOver())
				{
					return true;
				}
			}
			else if (buffer == "#")
			{
				if (game->flag(c, r))
				{
					std::cout << "Flagged Successfully: ";
					std::cout << game->bombsLeft() << " bombs left" << std::endl;
				}
				else
				{
					std::cout << ">> Already Revealed; Can't flag <<" << std::endl;
				}
				displayBoard(game);
			}
			std::cout << std::endl; //separate moves
		}
	}
	catch(EndGameException e)
	{
		game->revealBombs();
		displayBoard(game);
		return false;
	}
}
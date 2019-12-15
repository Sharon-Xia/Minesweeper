#include <iostream>
#include <string>
#include "Board.hpp" //Board(size, bombs)
#include "EndGameException.hpp"
#include "Array2d.hpp"
#include "Game.hpp"


int main()
{
	std::string input;
	Board* game = nullptr;
	do
	{
		std::cout << "Enter your desired level:" << std::endl;
		std::cout << "(EZ, MED, HARD) " << std::endl;
		std::cout << "Or type QUIT to quit" << std::endl;
		std::cout << ">> " ;
		std::getline(std::cin, input);

		if (input == "EZ")
		{
			game = new Board(9, 10);
		}
		else if (input == "MED")
		{
			game = new Board(16, 40);
		}
		else if (input == "HARD")
		{
			game = new Board(24, 99);
		}

		if (game != nullptr)
		{
			if (startGame(game))
			{
				std::cout << ">> CONGRATULATIONS! GAME WON! <<" << std::endl;
			}
			else
			{
				std::cout << ">> Sorry, GAME OVER <<" << std::endl;
			}
			std::cout << std::endl;
			delete game;
			game = nullptr;
		}
	}
	while (input != "QUIT");


	std::cout << ">> GG <<" << std::endl;
	return 0;
}


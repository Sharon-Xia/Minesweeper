#ifndef TILE_BOMB_HPP
#define TILE_BOMB_HPP

#include "tile.hpp"

class Bomb : public Tile 
{
public:
	Bomb()
	{}

	const std::string type() const
	{
		return "BOMB";
	}

private:

};

#endif
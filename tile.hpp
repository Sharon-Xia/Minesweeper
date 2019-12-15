#ifndef TILE_HPP
#define TILE_HPP
#include <string>

class Tile
{
public:
	Tile()
	:revealed{false}, nAdj{0}, flagged{false}
	{}

	~Tile() = default;

	bool reveal() // returns whether or not nearbyBombCount is 0
	{
		revealed = true;
		return (this->type() != "BOMB") and nearbyBombCount() == 0;
	}

	bool status() const
	{
		return revealed;
	}

	virtual const std::string type() const
	{
		return "NORMAL";
	}

	void incBombCount()
	{
		nAdj++;
	}

	int nearbyBombCount() const
	{
		return nAdj;
	}

	void flag() //flips flagged status
	{
		flagged = not flagged;
	}

	bool flagstatus()
	{
		return flagged;
	}

private:
	bool revealed;
	int nAdj; // num of bombs adjacent
	bool flagged;
};

#endif
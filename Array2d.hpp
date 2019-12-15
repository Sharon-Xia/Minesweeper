// FOUND ON INTERNET xd
// https://stackoverflow.com/questions/1768294/how-to-allocate-a-2d-array-of-pointers-in-c
// tweaked a little bit for this project tho

#ifndef Array2d_HPP
#define Array2d_HPP

#include "tile.hpp"
#include "tile_Bomb.hpp"

class Array2d
{
public:
    explicit Array2d(int w, int h)
    :m_data{new Tile*[w * h]}, WIDTH{w}, HEIGHT{h}
    {
    }

    ~Array2d() //destructor
    {
        for (int i = 0; i < (WIDTH * HEIGHT); ++i)
        {
            delete m_data[i];
        }
        delete[] m_data;
    }

    const Tile* operator()(int col, int row) const
    {
        return m_data [( row * WIDTH + col)];
    }

    Tile*& operator()(int col, int row)
    {
        // Assert col < WIDTH and row < HIEGHT
        return m_data [( row * WIDTH + col)];
    }

private:
Tile** m_data;
int WIDTH;
int HEIGHT;

};

#endif

// *** HOW TO USE ***
// Array2d< Object*, 10, 10 > myObjectArray;
// myObjectArray(5,6) = new Object();
// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "well.hxx"

WellBlock::WellBlock(Block  input, int type, int row, int col):
        topLeft(input.top_left()),
        bottomRight(input.bottom_right()),
        size(input.width),
        row(row),
        column(col),
        colorType(type)
{ }

Position
WellBlock::top_left() const
{
    return topLeft;
}

void
WellBlock::setColorType(int type){
    colorType = type;
}

bool
WellBlock::coveredByTetris(Block& block){

    if((bottomRight.x < block.top_left().x+1) ||
       (topLeft.x > block.bottom_right().x-1))
    {
        return false;
    }

    if((topLeft.y > block.bottom_right().y-1)||
       (bottomRight.y < block.top_left().y+1))
    {
        return false;
    }

    return true;
}

bool
WellBlock::touchByTetris(Block& block){
    if(((top_left().x +1) >= block.top_left().x) &&
       (bottomRight.x <= block.bottom_right().x + 1) &&
       (top_left().y <= block.bottom_right().y)){
        return true;
    }

    return false;
}

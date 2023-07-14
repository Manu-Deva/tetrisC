/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct for modeling the ball.


#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>


/// We will represent positions as GE211 `Posn<float>`s, which we alias
/// with the type name `Position`. This is a struct that could be
/// defined like so:
///
///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<int>;


/// We will represent velocities as GE211 `Dims<float>`s, which we alias
/// with the type name `Velocity`. This is a struct that could be
/// defined like so:
///
///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<int>;

using Block = ge211::Rect<int>;


///Represents a block
struct WellBlock
{

    WellBlock(Block input, int type, int row, int col);

    //
    // MEMBER FUNCTIONS
    //

    int colorType;

    void setColorType(int type);
    Position top_left() const;
    Position topLeft;
    Position bottomRight;
    int size;
    int row;
    int column;
    bool coveredByTetris(Block& block);
    bool touchByTetris(Block & block);
};


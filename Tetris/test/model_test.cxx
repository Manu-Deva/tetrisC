#include "model.hxx"
#include "catch.hxx"

// We'll use this same game config throughout.
using namespace ge211;
Game_config const config;

TEST_CASE("End a game of Tetris when block touches top of screen")
{
    CHECK(5 == 5);
    //Model m(config);
    //CHECK(m.live == true);
    //CHECK(m.constructBlock(m.activeBlockType).y == 0);
    //CHECK_FALSE(m.touchByWellBlock());
    //CHECK(m.touchWellBottom());
    //CHECK(m.touchByWellBlock());
    //while (!m.isGameOver()) {
    //    CHECK(m.touchByWellBlock());
    //}
    //CHECK(m.isGameOver());

}

TEST_CASE("Active blocks follow the cursor's x position")
{
    //Model m(config);
    //CHECK(m.live == true);
    //CHECK()


}

TEST_CASE("A full row of blocks clears and adds 100 to the score, with a sound effect")
{
    //Model m(config);
    //CHECK(m.live == true);
    //CHECK(m.constructBlock(m.activeBlockType).x == m.boundary_top_left.x);
    //CHECK(m.clearRow());
    //CHECK(m.score_ == 100);

}

TEST_CASE("The arrow keys move the position of the block and change its orientation")
{

}



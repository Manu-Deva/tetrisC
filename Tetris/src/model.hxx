/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/



#pragma once

#include "game_config.hxx"
#include "well.hxx"
#include <vector>


// The logical state of the game.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a model from a game configuration.
    //
    // The `= Game_config()` syntax makes the argument optional, in which case
    // it defaults to the default `Game_config`. That is, you can explicitly
    // create a `Game_config` to pass the `Model` constructor like so:
    //
    //     Game_config config;
    //     config.ball_radius = 2;
    //     Model model(config);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Game_config` (as defined in game_config.cpp):
    //
    //     Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Game_config`s into `Model`s if needed. You don't want that.
    explicit Model(Game_config const& config = Game_config());

    ///
    /// MEMBER FUNCTIONS
    ///

    void on_frame(double dt);

    int score() const
    { return score_; }
    ///
    /// MEMBER VARIABLES
    ///

    // The configuration parameters of the model. See game_config.hxx for a
    // description of what this determines. Models can be constructed with
    // different configurations, but the configuration never changes on an
    // existing model.
    Game_config const config;

    std::vector<WellBlock> bricks;
    // Game boundaries for the grid
    Position boundary_top_left;
    Position boundary_right_bottom;
    Position game_over_position;
    Position score_position;
    // Represents the block currently falling down
    int activeBlockType;
    float rotationDegree;
    Block   activeBlock;   // 2, square, 3, rectangle3, 4, rectangle4
    // Represents whether the game over has been reached
    bool live;
    /// Ensures that a dropped block stays on the grid
    void saveHistory();
    /// Checks if block contact exists
    bool touchByWellBlock() ;
    // Checks if there's contact on each side of the block
    bool touchWellBottom();
    bool touchWellLeftSide();
    bool touchWellRightSide();
    /// Removes all blocks from a full row
    bool clearRow();
    /// Moves current blocks down a row when a row has been cleared
    void shiftRow(int row);
    /// Resets the game to the beginning
    void reset();
    void block_to(int x);
    /// Uses the active state of the game as a checkpoint
    bool isGameOver();
    Block constructBlock(int type);

    int score_ = 0;
};


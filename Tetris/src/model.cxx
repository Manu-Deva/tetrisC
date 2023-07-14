// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"

static int const score_font_size = 40;
Model::Model(Game_config const& config)
        : config(config),
          boundary_top_left(0,0),
          boundary_right_bottom(0,0),
          game_over_position(0,0),
          score_position(900, 400),
          activeBlockType(rand() %5 +2),
          rotationDegree(0),
          live(true)
{
    // TODO: your code here
    reset();
}

void
Model::reset()
{
    bricks.clear();
    activeBlockType = rand() %3 +2;
    rotationDegree = 0;
    score_ = 0;
    live = true;
    for(int row = 0; row < config.brick_rows; row ++) {
        for(int col = 0; col < config.brick_cols; col ++) {
            int left_top_x = config.side_margin + col*(config.brick_dims()
                                                             .width + config.brick_spacing.width);
            int left_top_y = config.top_margin + row*(config.brick_dims()
                                                            .height + config.brick_spacing.height);
            Block brick = Block (left_top_x,
                                 left_top_y,
                                 config.brick_dims().width,
                                 config.brick_dims().height);
            WellBlock block(brick, 1, row, col);
            bricks.push_back(block);
        }
    }

    boundary_top_left = Position (config.side_margin,
                                  config.top_margin);

    game_over_position = Position ( config.side_margin,
                                    config.top_margin-100);

    boundary_right_bottom = Position (config.side_margin +
                                      (config.brick_cols)*(config.brick_dims().width +
                                                           config.brick_spacing.width) ,
                                      config.top_margin +
                                      (config.brick_rows)*
                                      (config.brick_dims().height +
                                       config.brick_spacing.height));
    activeBlock = constructBlock(activeBlockType);
}

bool
Model::isGameOver() {
    for ( WellBlock & block: bricks) {
        if(block.row == 0 && block.colorType != 1) {
            return true;

        }
    }
    return false;
}
void
Model::block_to(int x)
{
    activeBlock.x = x;
}
void
Model::saveHistory()
{
    for ( WellBlock & block: bricks) {
        if(block.coveredByTetris(activeBlock)) {
            block.colorType = activeBlockType;
        }
    }






        // check if game over
    if(isGameOver()) {
        live = false;
    }
}

/// clear the row
bool
Model::clearRow() {
    for (int row = 0; row < config.brick_rows; row++) {
        int count = 0;
        for (WellBlock &block: bricks) {
            if (block.row == row && block.colorType != 1) {
                count++;
            }
        }

        if (count == config.brick_cols) { // allfilled
            shiftRow(row);
            //view.play_wipe_effect();
            score_ += 100;
            return true;
        }
    }
    return false;
}


void
Model::shiftRow(int row) {

    int sortArray[config.brick_rows][config.brick_cols];
    for ( WellBlock & block: bricks) {
        sortArray[block.row][block.column] = block.colorType;
    }

    for( int i = row; i >=1 ; i --) {
        for ( WellBlock & block: bricks) {
            if( block.row == i)  {
                block.colorType = sortArray[i-1][block.column];
            }
        }
    }

    for ( WellBlock & block: bricks) {
        if( block.row == 0)  {
            block.colorType = 1;
        }
    }
}


void
Model::on_frame(double dt)
{
    if(!live){
        return;
    }
    activeBlock.y += 1;

    if( touchByWellBlock() || touchWellBottom()) {
        saveHistory();
        activeBlockType = rand() % 5 + 2;
        rotationDegree = 0;
        activeBlock = constructBlock(activeBlockType);
    }

}

Block
Model::constructBlock (int type) {
    int scalex = 2, scaley = 2;

    if(type == 3) {
        scalex = 3;
        scaley = 1;
    }
    if(type == 4) {
        scalex = 4;
        scaley = 1;
    }
    if(type == 5) {
        scalex = 3;
        scaley = 2;
    }
    if(type == 6) {
        scalex = 4;
        scaley = 2;
    }


    return Block( boundary_top_left.x,0,
                         config.unit_square_dims().width*scalex,
                         config.unit_square_dims().height*scaley);;
}

bool
Model::touchByWellBlock()  {
    for( WellBlock & block : bricks) {
        if(block.colorType != 1) {
            if(block.touchByTetris(activeBlock)) {
                return true;
            }
        }
    }
    return false;
}

bool
Model::touchWellBottom() {
    if ((activeBlock.y + activeBlock.height >=
         boundary_right_bottom.y)) {
        return true;
    }
    return false;
}

bool
Model::touchWellLeftSide() {
    if (activeBlock.x <= config.side_margin) {
        return true;
    }
    return false;
}

bool
Model::touchWellRightSide() {
    if ((activeBlock.x + activeBlock.width +
         config.brick_spacing.width) >
        boundary_right_bottom.x) {
        return true;
    }
    return false;
}


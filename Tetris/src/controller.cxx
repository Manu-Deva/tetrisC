// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "controller.hxx"
#include "model.hxx"

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Controller::Controller(Model& model)
        : model(model),
          view(model,
               mixer()
               )
{ }

///
/// CONTROLLER FUNCTIONS
///

// You can get a `Key` representing space with `ge211::Key::code(' ')`.
void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    if( key == ge211::Key::code(' ')) {
        model.reset();
        model.score_ = 1;
    }

    if (model.live) {
        if (key == ge211::Key::up()) { // up
            model.rotationDegree += 90.0;
            if (model.rotationDegree > 90) {
                model.rotationDegree = 0;
            }
            Position left_center = model.activeBlock.top_left();
            int temp = model.activeBlock.height;
            model.activeBlock.height = model.activeBlock.width;
            model.activeBlock.width = temp;
            model.activeBlock.x = left_center.x;
            model.activeBlock.y = left_center.y;
        }

        if (key == ge211::Key::down()) { // down

            model.activeBlock.y += 30;

            if( model.touchByWellBlock() || model.touchWellBottom()) {
                model.activeBlock.y -=30;
                return;
            }

        }

        if (key == ge211::Key::left()) { // left
            if (model.touchWellLeftSide() || model
                    .touchByWellBlock()) {
                return;
            } else {
                model.activeBlock.x -= model.config.brick_dims().width +
                                       model.config.brick_spacing.width;
                if( model.touchByWellBlock()) {
                    model.activeBlock.x += model.config.brick_dims().width +
                                           model.config.brick_spacing.width;
                    return;
                }
            }
        }

        if (key == ge211::Key::right()) { // right
            if (model.touchWellRightSide()|| model
                    .touchByWellBlock()) {
                return;
            }
            else {
                model.activeBlock.x += model.config.brick_dims().width +
                                       model.config.brick_spacing.width;
                if( model.touchByWellBlock()) {
                    model.activeBlock.x -= model.config.brick_dims().width +
                                           model.config.brick_spacing.width;
                    return;
                }
            }

        }
    }
}

void
Controller::clearrRow() {
    if (model.clearRow()) {
        view.play_wipe_effect();
    }
}


void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int>)
{
    // TODO: your code here
}


void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    if (position.x > model.activeBlock.x) {
        on_key(ge211::Key::right());
    };

    if (position.x < model.activeBlock.x) {
        on_key(ge211::Key::left());
    };
}



//
// Forwarding functions (done for you)
//

void
Controller::on_frame(double dt){
    model.on_frame(dt);
    clearrRow();
    view.resume_music();
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view.draw(sprites);
}

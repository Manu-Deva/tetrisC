// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "view.hxx"
#include "model.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
static ge211::Color const red_color {255, 0, 0};
static ge211::Color const green_color {0, 255, 0};
static ge211::Color const yellow_color {255, 255, 0};
static ge211::Color const blue_color {100, 142, 209};
static ge211::Color const orange_color {255, 165, 0};
static ge211::Color const magenta_color {191, 100, 210};

static ge211::Color const brick_color {100, 100, 100};
static int const score_font_size = 40;


///
/// VIEW CONSTRUCTOR
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
View::View(Model const& m,
           ge211::Mixer& mixer)
        : model(m),
          brick_sprite(m.config.brick_dims(), brick_color),

          brick_red_sprite(m.config.brick_dims(), red_color),
          brick_green_sprite(m.config.brick_dims(), green_color),
          brick_yellow_sprite(m.config.brick_dims(), yellow_color),
          brick_blue_sprite(m.config.brick_dims(), blue_color),
          brick_orange_sprite(m.config.brick_dims(), orange_color),
          brick_magenta_sprite(m.config.brick_dims(), magenta_color),

          square_sprite({2*m.config.unit_square_dims().width,
                         2*m.config.unit_square_dims().height}, red_color),

          rectangle3_sprite({3*m.config.unit_square_dims().width,
                             m.config.unit_square_dims().height},green_color),

          rectangle3x2_sprite({3*m.config.unit_square_dims().width,
                             2*m.config.unit_square_dims().height},blue_color),

          rectangle4_sprite({4*m.config.unit_square_dims().width,
                             m.config.unit_square_dims().height},yellow_color),

          rectangle4x2_sprite({4*m.config.unit_square_dims().width,
                             2*m.config.unit_square_dims().height},magenta_color),

          rectangle3_p_sprite({m.config.unit_square_dims().width,
                             3*m.config.unit_square_dims().height},green_color),

           rectangle3x2_p_sprite({2*m.config.unit_square_dims().width,
                               3*m.config.unit_square_dims().height},blue_color),

          rectangle4_p_sprite({m.config.unit_square_dims().width,
                             4*m.config.unit_square_dims().height},
                              yellow_color),
          rectangle4x2_p_sprite({2*m.config.unit_square_dims().width,
                               4*m.config.unit_square_dims().height},
                              magenta_color),

          game_over_sprite("Game Over. Press 'q' to quit or the spacebar to restart", sans),
          score_font_("sans.ttf", score_font_size),
          score_sprite_("0", score_font_),
          previous_score_(0),
          mixer(mixer)

{
    if (mixer.is_enabled()) {
        load_audio();
    }
}


///
/// VIEW FUNCTIONS
///

// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.
void
View::draw(ge211::Sprite_set& sprites)
{
   switch(model.activeBlockType) {
       case 2:
            sprites.add_sprite(square_sprite,
                               model.activeBlock.top_left(), 5);
            break;
       case 3:
           if(model.rotationDegree == 0) {
               sprites.add_sprite(rectangle3_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }
           else {
               sprites.add_sprite(rectangle3_p_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }
            break;
       case 4:
           if(model.rotationDegree == 0) {
               sprites.add_sprite(rectangle4_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }           else {
               sprites.add_sprite(rectangle4_p_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }
            break;
       case 5:
           if(model.rotationDegree == 0) {
               sprites.add_sprite(rectangle3x2_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }
           else {
               sprites.add_sprite(rectangle3x2_p_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }
           break;
       case 6:
           if(model.rotationDegree == 0) {
               sprites.add_sprite(rectangle4x2_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }           else {
               sprites.add_sprite(rectangle4x2_p_sprite,
                                  model.activeBlock.top_left(),
                                  5);
           }
   }

    for (const WellBlock & brick: model.bricks) {
        if(brick.colorType == 2) {
            sprites.add_sprite(brick_red_sprite,
                               brick.top_left(), 2);
        }
        if(brick.colorType == 3) {
            sprites.add_sprite(brick_green_sprite,
                               brick.top_left(), 3);
        }
        if(brick.colorType == 4) {
            sprites.add_sprite(brick_yellow_sprite,
                               brick.top_left(), 4);
        }
        if(brick.colorType == 5) {
            sprites.add_sprite(brick_blue_sprite,
                               brick.top_left(), 5);
        }
        if(brick.colorType == 6) {
            sprites.add_sprite(brick_magenta_sprite,
                               brick.top_left(), 6);
        } else {
            sprites.add_sprite(brick_sprite,
                               brick.top_left(), -1);
        }
    }

    if(!model.live) {
        sprites.add_sprite(game_over_sprite, model.game_over_position,
                           5);
    }

    if (model.score() != previous_score_) {
        ge211::Text_sprite::Builder builder(score_font_);
        builder << model.score();
        score_sprite_.reconfigure(builder);
    }
    sprites.add_sprite(score_sprite_, {900, 400}, 5);

    if (model.live == false) {
        ge211::Text_sprite::Builder builder(score_font_);
        //model.score_ = 0;
        builder << model.score();
        score_sprite_.reconfigure(builder);
    }
}

void
View::play_place_effect() const
{
    mixer.try_play_effect(place_sound_);
}

void
View::play_wipe_effect() const
{
    mixer.try_play_effect(wipe_sound_);
}
void
View::resume_music() const
{
    if (mixer.get_music_state() == ge211::Mixer::State::paused) {
        mixer.resume_music();
    }
}
void
View::load_audio()
{
    place_sound_.try_load("mixkit-arcade-retro-changing-tab-206.wav", mixer);
    wipe_sound_.try_load("mixkit-futuristic-robotic-fast-sweep-171.wav", mixer);

    try {
        // To enable background music, put a file named bg_music.ogg
        // in the Resources/ directory.
        if (bg_music_.try_load("bensound-dontforget.mp3", mixer)) {
            mixer.play_music(bg_music_);
        }
    } catch (ge211::Environment_error const& exn) {
        ge211::internal::logging::warn(exn.what())
                << "To enable background music, put a file named\n"
                << "bensound-dontforget.mp3" << " in the Resources/ directory.";
    }
}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model.config.scene_dims;
}


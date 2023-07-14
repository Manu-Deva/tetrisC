// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include <ge211.hxx>

// Forward declaration of our model struct. This lets us use references
// to Model in this file even though the definition isn’t visible. (Just
// like in C.)
struct Model;

class View
{
public:
    //
    // CONSTRUCTOR
    //

    /// Constructs a `View` given a const reference to the model that
    /// stores the actual state of the game. This lets the view observe
    /// the model’s state but not modify it.
    ///
    /// The word `explicit` means that this constructor doesn't define
    /// an implicit conversion whereby you could pass a `Model` to a
    /// function that expects a `View` and have it work.
    View(
            const Model& model,
            ge211::Mixer& mixer
            );

    //
    // MEMBER FUNCTIONS
    //

    /// Returns the size of the window as given by `config.scene_dims`.
    ge211::Dims<int> initial_window_dimensions() const;

    /// Renders all the game entities to the screen.
    void draw(ge211::Sprite_set&);
    void play_place_effect() const;
    /// Plays a sound effect when a row is full and cleared
    void play_wipe_effect() const;
    /// Loads music and sound effects into the game
    void load_audio();
    /// Resumes music when the track ends
    void resume_music() const;


    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the view doesn't
    /// own the model but has access to it. Thus, the client of the view
    /// (controller.cxx) must have or create a `Model` first and then
    /// pass that by reference to the `View` constructor.
    Model const& model;
    ge211::Font sans{"sans.ttf", 30};
    // Text sprites for the game
    ge211::Text_sprite game_over_sprite;

    // Sprites representing each of the blocks
    ge211::Rectangle_sprite const brick_sprite;
    ge211::Rectangle_sprite const brick_red_sprite;
    ge211::Rectangle_sprite const brick_green_sprite;
    ge211::Rectangle_sprite const brick_yellow_sprite;
    ge211::Rectangle_sprite const brick_blue_sprite;
    ge211::Rectangle_sprite const brick_orange_sprite;
    ge211::Rectangle_sprite const brick_magenta_sprite;
    ge211::Rectangle_sprite const square_sprite;
    ge211::Rectangle_sprite const rectangle3_sprite;
    ge211::Rectangle_sprite const rectangle3x2_sprite;
    ge211::Rectangle_sprite const rectangle4_sprite;
    ge211::Rectangle_sprite const rectangle4x2_sprite;
    ge211::Rectangle_sprite const rectangle3_p_sprite;
    ge211::Rectangle_sprite const rectangle3x2_p_sprite;
    ge211::Rectangle_sprite const rectangle4_p_sprite;
    ge211::Rectangle_sprite const rectangle4x2_p_sprite;
    // Sprites for the font
    ge211::Font score_font_;
    ge211::Text_sprite score_sprite_;
    std::size_t previous_score_;


    // Music elements
    ge211::Mixer& mixer;
    ge211::Music_track bg_music_;
    ge211::Sound_effect place_sound_;
    ge211::Sound_effect wipe_sound_;


};

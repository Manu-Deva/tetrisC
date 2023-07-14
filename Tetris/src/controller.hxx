// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
    //
    // CONSTRUCTOR
    //

    /// Constructs a `Controller` given a reference to the model that
    /// stores the actual state of the game.
    ///
    /// The word `explicit` means that this constructor doesn't define
    /// an implicit conversion whereby you could pass a `Model` to a
    /// function that expects a `Controller` and have it work.
    explicit Controller(Model&);


    //
    // MEMBER FUNCTIONS
    //

    /// Defines how the game responds to key events. There are two keys
    /// recognized:
    ///
    ///  - On 'q', quits.
    ///
    ///  - On ' ', tells the model to launch the ball.
    void on_key(ge211::Key) override;

    /// Defines how the game responds to mouse clicks (Moving the ball with the mouse).
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;

    void on_mouse_move(ge211::Posn<int>) override;

    /// clears the row to add a sound effect (intentional double r)
    void clearrRow() ;


    //
    // These three “forwarding” member functions are called by the GE211
    // framework and delegate to the other components (model or view).
    // This is because GE211 only knows about the controller, and thus
    // the controller has to mediate between GE211 and the model and
    // view.
    //

    /// The GE211 framework calls this to updates the game state to
    /// reflect the passage of time. This function is passed `dt`, the
    /// elapsed time in seconds since the previous frame. The
    /// implementation in controller.cxx delegates to model.on_frame().
    void on_frame(double dt) override;

    /// The GE211 framework calls this to find out how big to make the
    /// window. The implementation in controller.cxx delegates this to
    /// view.initial_window_dimensions(), since the view show know how
    /// big it wants the window to be.
    ge211::Dims<int> initial_window_dimensions() const override;

    /// The GE211 framework calls this at regular intervals to ask the
    /// game what should appear on the screen. It’s given a reference to
    /// an empty set of sprites (corresponding to painting the scene
    /// from scratch), to which it adds sprites at various positions,
    /// which the framework then renders to the screen. The
    /// implementation in controller.cxx delegates to view.draw(), since
    /// visuals are the view’s job.
    void draw(ge211::Sprite_set&) override;


    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the controller
    /// doesn't own the model but has access to it. Thus, the client of
    /// the controller (brick_out.cxx) must create a `Model` first and
    /// then pass that by reference to the `Controller` constructor.
    Model& model;

    /// This is the view, which contains the game’s data and code for
    /// displaying the state of the model to the screen.
    View view;
};

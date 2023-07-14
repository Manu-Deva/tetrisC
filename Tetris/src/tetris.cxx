// IT'S OKAY TO CHANGE THIS FILE, BUT YOU DON'T HAVE TO.

#include "model.hxx"
#include "controller.hxx"

int
main()
{
    Model model;
    Controller controller(model);

    controller.run();
}

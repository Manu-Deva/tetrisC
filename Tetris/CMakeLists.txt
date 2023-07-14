cmake_minimum_required(VERSION 3.3)
project(tetris CXX)
include(.cs211/cmake/CMakeLists.txt)

# Defines a variable to stand for the three .cxx files that implement
# the model.
set(MODEL_SRC
        src/game_config.cxx
        src/well.cxx
        src/model.cxx)

# Adds a program named `brick_out` built from src/brick_out.cxx and
# the common model files.
add_program(tetris
        src/tetris.cxx
        src/controller.cxx
        src/view.cxx
        ${MODEL_SRC})
target_link_libraries(tetris ge211)

# Adds a test program named `ball_test` built from test/ball_test.cxx
# and the common model files.
add_test_program(model_test
        test/model_test.cxx
        ${MODEL_SRC})
target_link_libraries(model_test ge211)

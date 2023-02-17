cmake_minimum_required(VERSION 3.5)

project(AutoFlappyRefactored)

# Add sub directories
# This is how we grab the library frameworks.
# Also this is what allows to do includes such as #include <Logger.h>, and etc.
add_subdirectory(AI_Flappy)

add_subdirectory(Main)
set(PROJECT_NAME AI_Flappy)
#set(CMAKE_CXX_FLAGS "-std=c++20")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(${PROJECT_NAME})

# This is how we only grab header files and add them to the main project.
#add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME} src/Window.cpp)
add_library(UI::UI1 ALIAS ${PROJECT_NAME})

# Lets us call library1 with an cmake alias that referred to as sub::lib1
# Another example is: Log::Log1 (This doesnt have to be similar, but its best that it is)
# This alias is how we call this library in the main CMakeLists.txt

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/core
    ${PROJECT_SOURCE_DIR}/include/common
    ${PROJECT_SOURCE_DIR}/include/genetics
    ${PROJECT_SOURCE_DIR}/include/AI
    ${PROJECT_SOURCE_DIR}/include/graphics
    ${PROJECT_SOURCE_DIR}/include/game
    ${PROJECT_SOURCE_DIR}/include/events
    ${PROJECT_SOURCE_DIR}/include/ML

)

# target_link_libraries(${PROJECT_NAME} PUBLIC "include" "include/core" "include/common" "include/genetics" "include/AI" "include/graphics" "include/game")

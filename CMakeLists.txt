cmake_minimum_required(VERSION 3.0.0)

SET(PROJECT_NAME opengl_window_example)

project(${PROJECT_NAME} VERSION 0.1.0)

include(CTest)
enable_testing()

# VERSION USE: This is going to be a message notifying just in case, I forget.
# VERSION: Cmake works on an M1 Mac 2022 December (Current month)
# This CMAKE Will be able to compile the following libraries
# OpenCV, SFML, SDL, OPENGL on mac

#################[SFML]##################
# Add to detect SFML Libraries here!
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)

#################[SDL2]##################
# Adding detect SDL2 Libraries here!
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#################[OPENCV]##################
# Find Package
# Handle in searching for OpenCV framwork.
#set( OpenCV_DIR "C:/Program Files/opencv/build" )
option( OpenCV_STATIC OFF )
find_package( OpenCV REQUIRED )

# Searching for OpenGL frameworks
# OpenGL
find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


# Handling our file structures here.
# This allows us to include our libraries throughout this entire project.
# This lets us get access to our includes and headers
file(GLOB
    "main.cpp"
    "-IXenosGameEngine/include/*.h"
    "XenosGameEngine/include/Events/*.h"
)



# Globalizes our *.cpp files
file(
   GLOB
   SRC "XenosGameEngine/src/*.cpp"
)

add_executable(${PROJECT_NAME} main.cpp ${SRC})


# LINK OUR XENOS GAME ENIGINE LIBRARY THROUGH THE CMAKE FILE WE CREATED IN THE DIRECTORY
# Try to include my own headers...
# target_include_directories(${PROJECT_NAME} PUBLIC "XenosGameEngine")

# NOTE: These below here are going to grab our targeted and link our libraries opencv, sfml, sdl, and opengl

# Target including directories and libraries for SFML only!
# This includes are specifics to SFML
target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
if (UNIX)
   target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

# Copy res dir to the binary directory
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC)
   foreach(lib ${SFML_LIBS})
      get_target_property(lib_path ${lib} LOCATION)
      file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   endforeach()
endif(MSVC)



# Helps link our opencv libraries for C++ on mac.
# This condition, checks if OpenCV the library has been found
# This is what helps us to dynamically link our opencv libraries for this C++ project.
if( OpenCV_FOUND )
  # Additional Include Directories
  include_directories( ${OpenCV_INCLUDE_DIRS} )

  # Additional Library Directories
  link_directories( ${OpenCV_LIB_DIR} )

  # Additional Dependencies
  target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
else()
    message("Opencv library not found")
endif()



# Help link our SDL libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Help for linking the opengl libraries
# Linking the link that helped get opengl working: 
# https://carette.xyz/posts/opengl_and_cpp_on_m1_mac/
# target_link_directories(${PROJECT_NAME} PUBLIC $(OPENGL_INCLUDE_DIR)) # Not gonna delete this commented, just so I know this wont work for future ref.

# Linking the libraries for Cocoa, OpenGL, IOKit, and glfw
target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} GLEW::GLEW) # This helps us get rid of the "___glewGenBuffers" reference error
# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build

# Include any dependencies generated for this target.
include Main/CMakeFiles/Main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Main/CMakeFiles/Main.dir/compiler_depend.make

# Include the progress variables for this target.
include Main/CMakeFiles/Main.dir/progress.make

# Include the compile flags for this target's objects.
include Main/CMakeFiles/Main.dir/flags.make

Main/CMakeFiles/Main.dir/main.cpp.o: Main/CMakeFiles/Main.dir/flags.make
Main/CMakeFiles/Main.dir/main.cpp.o: /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/Main/main.cpp
Main/CMakeFiles/Main.dir/main.cpp.o: Main/CMakeFiles/Main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Main/CMakeFiles/Main.dir/main.cpp.o"
	cd /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Main/CMakeFiles/Main.dir/main.cpp.o -MF CMakeFiles/Main.dir/main.cpp.o.d -o CMakeFiles/Main.dir/main.cpp.o -c /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/Main/main.cpp

Main/CMakeFiles/Main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Main.dir/main.cpp.i"
	cd /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/Main/main.cpp > CMakeFiles/Main.dir/main.cpp.i

Main/CMakeFiles/Main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Main.dir/main.cpp.s"
	cd /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/Main/main.cpp -o CMakeFiles/Main.dir/main.cpp.s

# Object files for target Main
Main_OBJECTS = \
"CMakeFiles/Main.dir/main.cpp.o"

# External object files for target Main
Main_EXTERNAL_OBJECTS =

Main/Main: Main/CMakeFiles/Main.dir/main.cpp.o
Main/Main: Main/CMakeFiles/Main.dir/build.make
Main/Main: AI_Flappy/libAI_Flappy.a
Main/Main: /opt/homebrew/lib/libsfml-graphics.2.5.1.dylib
Main/Main: /opt/homebrew/lib/libopencv_gapi.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_stitching.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_alphamat.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_aruco.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_barcode.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_bgsegm.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_bioinspired.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_ccalib.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_dnn_objdetect.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_dnn_superres.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_dpm.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_face.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_freetype.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_fuzzy.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_hfs.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_img_hash.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_intensity_transform.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_line_descriptor.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_mcc.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_quality.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_rapid.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_reg.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_rgbd.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_saliency.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_sfm.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_stereo.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_structured_light.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_superres.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_surface_matching.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_tracking.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_videostab.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_viz.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_wechat_qrcode.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_xfeatures2d.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_xobjdetect.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_xphoto.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libSDL2.dylib
Main/Main: /usr/local/lib/libglfw3.a
Main/Main: /opt/homebrew/lib/libGLEW.2.2.0.dylib
Main/Main: /opt/homebrew/lib/libsfml-window.2.5.1.dylib
Main/Main: /opt/homebrew/lib/libsfml-system.2.5.1.dylib
Main/Main: /opt/homebrew/lib/libopencv_shape.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_highgui.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_datasets.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_plot.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_text.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_ml.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_phase_unwrapping.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_optflow.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_ximgproc.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_video.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_videoio.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_imgcodecs.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_objdetect.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_calib3d.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_dnn.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_features2d.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_flann.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_photo.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_imgproc.4.6.0.dylib
Main/Main: /opt/homebrew/lib/libopencv_core.4.6.0.dylib
Main/Main: Main/CMakeFiles/Main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Main"
	cd /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Main/CMakeFiles/Main.dir/build: Main/Main
.PHONY : Main/CMakeFiles/Main.dir/build

Main/CMakeFiles/Main.dir/clean:
	cd /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main && $(CMAKE_COMMAND) -P CMakeFiles/Main.dir/cmake_clean.cmake
.PHONY : Main/CMakeFiles/Main.dir/clean

Main/CMakeFiles/Main.dir/depend:
	cd /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/Main /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main /Users/aaronher/VSCodeProjects/C++/SFML/AutoFlappyRefactored/build/Main/CMakeFiles/Main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Main/CMakeFiles/Main.dir/depend


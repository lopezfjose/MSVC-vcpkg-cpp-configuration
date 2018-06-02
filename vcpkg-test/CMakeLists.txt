# CMakeList.txt : CMake project for vcpkg-test, include source and define
# project specific logic here.
#
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)

ENABLE_TESTING ()

FIND_PACKAGE (GTest REQUIRED)

FIND_PATH (CATCH_INCLUDE_DIR catch.hpp)
INCLUDE_DIRECTORIES (${CATCH_INCLUDE_DIR})
#FIND_PACKAGE (sdl2 REQUIRED)

# Add source to this project's executable.
ADD_EXECUTABLE (vcpkgtest "vcpkg-test.cpp" "vcpkg-test.h")

# TODO: Add tests and install targets if needed.
# TARGET_LINK_LIBRARIES (vcpkgtest sdl2)
TARGET_LINK_LIBRARIES (vcpkgtest PRIVATE GTest::GTest GTest::Main)

ADD_TEST (AllTestsInMain vcpkgtest)

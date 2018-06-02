

# MSVC-vcpkg-cpp-configuration

Sample code showing how to configure vcpkg for development of open-source C++ libraries. The following just a basic configuration that will run either the Catch2 unit testing framework, or GTest, Google's C++ test framework.

This configuration assumes both GTest and Catch have been installed via vcpkg and have been made availble system-wide using ```vcpkg integrate install```. Also, the ```CMakeSettings.json``` file is included here to show the required configuration settings for configuration under Visual Studio 15 2017.

#### Directory Structure:
```
vcpkg-test
|- .gitignore
|- README.md
|- LICENSE
|- CMakeSettings.json
|- CMakeLists.txt
|- vcpkg-test
   |- CMakeLists.txt
   |- vcpkg-test.cpp
   |- vcpkg-test.h
    
```

The following file is my configuration file in order to be able to integrate `vcpkg` libraries into my code. <b>Please remember that our path's will probably differ so don't forget to modify those accordingly, especially the location or your `vcpkg.cmake` file.</b>



#### CMakeSettings.json
```json
Snippet

{
  "configurations": [
    {
      "name": "x86-Debug",
      "generator": "Visual Studio 15 2017",
      "configurationType": "Debug",
      "inheritEnvironments": [ "msvc_x86" ],
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\install\\${name}",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "-m -v:minimal",
      "ctestCommandArgs": "",
      "variables": [
        {
          "name": "CMAKE_TOOLCHAIN_FILE",
          "value": "C:\\Source-Code\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
        }
      ] 
    },
    {
      "name": "x86-Release",
      "generator": "Visual Studio 15 2017",
      "configurationType": "RelWithDebInfo",
      "inheritEnvironments": [ "msvc_x86" ],
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\install\\${name}",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "-m -v:minimal",
      "ctestCommandArgs": ""
    },
    {
      "name": "x64-Debug",
      "generator": "Visual Studio 15 2017 Win64",
      "configurationType": "Debug",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\install\\${name}",
      "cmakeCommandArgs": "-Thost=x64",
      "buildCommandArgs": "-m -v:minimal",
      "ctestCommandArgs": "",
      "variables": [
        {
          "name": "CMAKE_TOOLCHAIN_FILE",
          "value": "C:\\Source-Code\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
        }
      ]
    },
    {
      "name": "x64-Release",
      "generator": "Visual Studio 15 2017 Win64",
      "configurationType": "RelWithDebInfo",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\install\\${name}",
      "cmakeCommandArgs": "-Thost=x64",
      "buildCommandArgs": "-m -v:minimal",
      "ctestCommandArgs": "",
      "variables": [
        {
          "name": "CMAKE_TOOLCHAIN_FILE",
          "value": "C:\\Source-Code\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
        }
      ]
    },
    {
      "name": "Linux-Debug",
      "generator": "Unix Makefiles",
      "remoteMachineName": "${defaultRemoteMachineName}",
      "configurationType": "Debug",
      "remoteCMakeListsRoot": "/var/tmp/src/${workspaceHash}/${name}",
      "cmakeExecutable": "/usr/local/bin/cmake",
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\install\\${name}",
      "remoteBuildRoot": "/var/tmp/build/${workspaceHash}/build/${name}",
      "remoteInstallRoot": "/var/tmp/build/${workspaceHash}/install/${name}",
      "remoteCopySources": true,
      "remoteCopySourcesOutputVerbosity": "Normal",
      "remoteCopySourcesConcurrentCopies": "10",
      "remoteCopySourcesMethod": "rsync",
      "remoteCopyBuildOutput": false,
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_x64" ]
    },
    {
      "name": "Linux-Release",
      "generator": "Unix Makefiles",
      "remoteMachineName": "${defaultRemoteMachineName}",
      "configurationType": "Release",
      "remoteCMakeListsRoot": "/var/tmp/src/${workspaceHash}/${name}",
      "cmakeExecutable": "/usr/local/bin/cmake",
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\${workspaceHash}\\install\\${name}",
      "remoteBuildRoot": "/var/tmp/build/${workspaceHash}/build/${name}",
      "remoteInstallRoot": "/var/tmp/build/${workspaceHash}/install/${name}",
      "remoteCopySources": true,
      "remoteCopySourcesOutputVerbosity": "Normal",
      "remoteCopySourcesConcurrentCopies": "10",
      "remoteCopySourcesMethod": "rsync",
      "remoteCopyBuildOutput": false,
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "inheritEnvironments": [ "linux_x64" ]
    }
  ]
}
```

#### Top-Level CMake File Configuration:
```
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)
PROJECT ("vcpkg-test")

ADD_SUBDIRECTORY ("vcpkg-test")
```

#### Source Directory CMake File Configuration:
```
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)
ENABLE_TESTING ()

FIND_PACKAGE (GTest REQUIRED)

FIND_PATH (CATCH_INCLUDE_DIR catch.hpp)
INCLUDE_DIRECTORIES (${CATCH_INCLUDE_DIR})

ADD_EXECUTABLE (vcpkgtest "vcpkg-test.cpp" "vcpkg-test.h")
TARGET_LINK_LIBRARIES (vcpkgtest PRIVATE GTest::GTest GTest::Main)

ADD_TEST (AllTestsInMain vcpkgtest)
```

#### vcpkg-test.h
```c++
Snippet

#pragma once
 
#include <cstdlib>
 
#include <iostream>
 
#include <boost/program_options.hpp>
 
#define CATCH_CONFIG_RUNNER
#include <Catch/catch.hpp>
 
#include <gtest/gtest.h>
```

#### vcpkg-test.cpp (Catch Version)
```c++
#include "vcpkg-test.h"
 
// Sample (incorrect) function for catch and gtest unit testing frameworks
unsigned int factorial(const unsigned int number)
{
return ((number <= 1) ? number : factorial(number - 1) * number);
}
 
TEST_CASE("Compute Factorials", "[factorial]")
{
 REQUIRE(factorial(1) == 1);
 REQUIRE(factorial(2) == 2);
 REQUIRE(factorial(3) == 6);
}
 
int main(int argc, char *argv[])
{
    return Catch::Session().run(argc, argv);
}
```

#### vcpkg-test.cpp (GTest Version)
```c++
#include "vcpkg-test.h"
 
// Sample (incorrect) function for catch and gtest unit testing frameworks
unsigned int factorial(const unsigned int number)
{
return ((number <= 1) ? number : factorial(number - 1) * number);
}

TEST(TestingConfiguration, BasicTest)
{
 EXPECT_EQ(0, 1);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
```

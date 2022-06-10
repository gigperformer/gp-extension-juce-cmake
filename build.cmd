@echo off

:: Build configuration - could be "Debug" as well
set BUILD_CONFIGURATION=Release
set BUILD_DIR=build\%BUILD_CONFIGURATION%

::Create a build directory if it's not already there
mkdir %BUILD_DIR%

::Change to the build directory
cd %BUILD_DIR%

::Create the configuration file using cmake
cmake ..\..

::Now build the project
cmake --build . --config %BUILD_CONFIGURATION%

:: Install the extension
cmake --install . --config %BUILD_CONFIGURATION%

::Go back to the starting folder
cd ..\..

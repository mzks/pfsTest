cmake_minimum_required(VERSION 3.5)
project(pfsTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bench/GlobalSetup.mac
    bench/pfs.mac
    bench/primaryGeneratorSetup.mac
    bench/verboseSetup.mac
    bench/visSetup_Simplex.mac
    build/CMakeFiles/3.6.2/CompilerIdC/CMakeCCompilerId.c
    build/CMakeFiles/3.6.2/CompilerIdCXX/CMakeCXXCompilerId.cpp
    build/CMakeFiles/feature_tests.c
    build/CMakeFiles/feature_tests.cxx
    build/b.sh
    source/include/Geometry.hh
    source/include/PrimaryGenerator.hh
    source/include/UserActionInitialization.hh
    source/src/Geometry.cc
    source/src/PrimaryGenerator.cc
    source/src/UserActionInitialization.cc)

add_executable(pfsTest ${SOURCE_FILES})
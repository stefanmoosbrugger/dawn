##===------------------------------------------------------------------------------*- CMake -*-===##
##                          _                      
##                         | |                     
##                       __| | __ ___      ___ ___  
##                      / _` |/ _` \ \ /\ / / '_  | 
##                     | (_| | (_| |\ V  V /| | | |
##                      \__,_|\__,_| \_/\_/ |_| |_| - Compiler Toolchain
##
##
##  This file is distributed under the MIT License (MIT). 
##  See LICENSE.txt for details.
##
##===------------------------------------------------------------------------------------------===##

include(mchbuildAddUnittest)

# dawn_add_unittest_impl
# ----------------------
#
# Compile the given objects into a runnable unittest executable (.exe) and register it within CTest.
# The executable will be stored in ${CMAKE_BINARY_DIR}/bin/unittest.
#
#    NAME:STRING=<>     - Name of the unittest exectuable as well as the CMake target to build it.
#    SOURCES:STRING=<>   - List of source files making up the exectuable.
#
macro(dawn_add_unittest_impl)
  cmake_parse_arguments(ARG "" "NAME" "SOURCES" ${ARGN})

  if(NOT("${ARG_UNPARSED_ARGUMENTS}" STREQUAL ""))
    message(FATAL_ERROR "dawn_add_unittest_impl: invalid argument ${ARG_UNPARSED_ARGUMENTS}")
  endif()

  mchbuild_add_unittest(
    NAME ${ARG_NAME}
    SOURCES ${ARG_SOURCES}
    DEPENDS DawnUnittestStatic DawnStatic DawnCStatic ${DAWN_EXTERNAL_LIBRARIES} gtest
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/unittest
    GTEST_ARGS --gtest_color=yes
  )
endmacro()

add_subdirectory(dawn)
add_subdirectory(dawn-c)

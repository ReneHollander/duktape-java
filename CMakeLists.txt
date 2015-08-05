cmake_minimum_required (VERSION 2.8.11)

find_package(JNI)
if (JNI_FOUND)
    include_directories(${JNI_INCLUDE_DIRS})
else()
    MESSAGE(FATAL_ERROR "Could not find JNI")
endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Os -flto")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Os -flto")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(C_SRC_PATH ./src/main/c)
include_directories(${C_SRC_PATH}/include)
add_library(duktape-java SHARED
    ${C_SRC_PATH}/duktape.c
    ${C_SRC_PATH}/memoryinfo.cc
    ${C_SRC_PATH}/refs.cc
    ${C_SRC_PATH}/cache.cc
    ${C_SRC_PATH}/helper.cc
    ${C_SRC_PATH}/objectwrapper.cc
    ${C_SRC_PATH}/duktape-java.cc
    ${C_SRC_PATH}/duk-array.cc
    ${C_SRC_PATH}/duk-object.cc
    ${C_SRC_PATH}/duk-function.cc
    ${C_SRC_PATH}/duk-referenced-value.cc
)
target_link_libraries(duktape-java -lm)

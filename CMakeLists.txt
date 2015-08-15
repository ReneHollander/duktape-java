cmake_minimum_required (VERSION 2.8.11)

find_package(JNI)
if (JNI_FOUND)
    include_directories(${JNI_INCLUDE_DIRS})
else()
    MESSAGE(FATAL_ERROR "Could not find JNI")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c99")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -std=c99 -Os -flto -fstrict-aliasing -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections -s -fno-exceptions -fno-rtti -fno-ident")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11 -Os -flto -fstrict-aliasing -fomit-frame-pointer -ffunction-sections -fdata-sections -Wl,--gc-sections -s -fno-exceptions -fno-rtti -fno-ident")

set(CMAKE_C_CXX_FLAGS "'-DDUK_OPT_PANIC_HANDLER(code,msg)={}'")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_CXX_FLAGS}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(C_SRC_PATH ./src/main/c)
add_library(duktape-java SHARED
    ${C_SRC_PATH}/cache.h
    ${C_SRC_PATH}/cache.cc
    ${C_SRC_PATH}/duk-array.h
    ${C_SRC_PATH}/duk-array.cc
    ${C_SRC_PATH}/duk-buffer.h
    ${C_SRC_PATH}/duk-buffer.cc
    ${C_SRC_PATH}/duk-error.h
    ${C_SRC_PATH}/duk-error.cc
    ${C_SRC_PATH}/duk-function.h
    ${C_SRC_PATH}/duk-function.cc
    ${C_SRC_PATH}/duk-java-function.h
    ${C_SRC_PATH}/duk-java-function.cc
    ${C_SRC_PATH}/duk-memory-allocator.h
    ${C_SRC_PATH}/duk-memory-allocator.cc
    ${C_SRC_PATH}/duk-object.h
    ${C_SRC_PATH}/duk-object.cc
    ${C_SRC_PATH}/duk-user-data.h
    ${C_SRC_PATH}/duktape.h
    ${C_SRC_PATH}/duktape.c
    ${C_SRC_PATH}/duktape-java.h
    ${C_SRC_PATH}/duktape-java.cc
    ${C_SRC_PATH}/helper.h
    ${C_SRC_PATH}/helper.cc
    ${C_SRC_PATH}/native-helper.h
    ${C_SRC_PATH}/native-helper.cc
    ${C_SRC_PATH}/refs.h
    ${C_SRC_PATH}/refs.cc
)
target_link_libraries(duktape-java -lm)

cmake_minimum_required (VERSION 2.8.11)

find_package(JNI)

if (JNI_FOUND)
    include_directories(${JNI_INCLUDE_DIRS})
else()
    MESSAGE(FATAL_ERROR "Could not find JNI")
endif()


set(C_SRC_PATH ./src/main/c)
add_library(duktape-java SHARED ${C_SRC_PATH}/duktape.c ${C_SRC_PATH}/duktape-java.c)
# add_executable(duktape-java ${C_SRC_PATH}/duktape.c ${C_SRC_PATH}/duktape-java.c)
target_link_libraries(duktape-java -lm)

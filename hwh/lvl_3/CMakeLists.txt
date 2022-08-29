cmake_minimum_required(VERSION 3.14)

project(dictionary)

option(PRINT_QUADS "PRINT_QUADS" OFF)

set(LIB hashtable)

add_subdirectory(lib)

target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB})

set(SRCS

    src/main.c
    src/strs_pair.c
)
set (HEADER include/strs_pair.c.h)
set (EXEC_FILE "hwh_lvl_3")

add_executable(${EXEC_FILE} ${SRCS})
target_include_directories(${EXEC_FILE} PRIVATE include)
target_include_directories(${EXEC_FILE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB})
target_link_libraries(${EXEC_FILE} PUBLIC ${LIB})

if(PRINT_QUADS)
  add_compile_definitions(PRINT_QUADS)
endif()
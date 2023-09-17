set(LIBRARY png-merge)

file(GLOB_RECURSE SOURCES "*.c")

add_library(${LIBRARY} STATIC ${SOURCES})
target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
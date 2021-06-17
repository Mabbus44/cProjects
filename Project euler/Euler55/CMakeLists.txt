project(euler55)

add_library(euler55 STATIC Number.cpp)
add_executable(euler55 main.cpp)

install(TARGETS euler55 RUNTIME DESTINATION bin)

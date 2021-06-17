project(euler56)

add_library(euler56 STATIC Number.cpp)
add_executable(euler56 main.cpp)

install(TARGETS euler56 RUNTIME DESTINATION bin)

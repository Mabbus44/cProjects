project(euler57)

add_library(euler57 STATIC Number.cpp)
add_executable(euler57 main.cpp)

install(TARGETS euler57 RUNTIME DESTINATION bin)

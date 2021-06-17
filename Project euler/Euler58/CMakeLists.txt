project(euler58)

set(myProjectResources "/home/rasmsus/c++ projects/PrimeList/primelist.cpp" main.cpp)
add_executable(euler58 ${myProjectResources})

install(TARGETS euler58 RUNTIME DESTINATION bin)

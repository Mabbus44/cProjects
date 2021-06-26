COPY main.cpp main2.cpp
TYPE main2.cpp | MORE /P > main2.cpp
COPY main2.cpp main.cpp
DEL main2.cpp
timeout 5
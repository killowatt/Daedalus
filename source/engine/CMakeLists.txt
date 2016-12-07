set(ENGINE_SOURCES
    Main.cpp
    Test.cpp
)

set(ENGINE_HEADERS
    Test.h
)

add_executable(greetings ${ENGINE_SOURCES} ${ENGINE_HEADERS})
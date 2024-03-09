cmake_minimum_required(VERSION 3.5)

project(_MyChat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(_MyChat main.cpp
    User.cpp User.h
    TArray.h
    Msg.cpp Msg.h
    Chat.cpp Chat.h
    Functions.cpp Functions.h
    README.md



)

include(GNUInstallDirs)
install(TARGETS _MyChat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.16)

project(MultiDimRootFinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NR3_DIR "../NR_C301/code")
set(NR3_UTIL_DIR "../include")

add_executable(run MultiDimRoots.cpp)

target_include_directories(run PRIVATE ${NR3_DIR} ${NR3_UTIL_DIR})

include(GNUInstallDirs)
install(TARGETS run
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
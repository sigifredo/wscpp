project(wscpp)
cmake_minimum_required(VERSION 2.8.3)

include("config/wscpp.cmake")
include("config/deps.cmake")
include("config/install.cmake")

set (WSCPP_HDRS
)

set (WSCPP_SRCS
)

add_executable(wscpp ${WSCPP_SRCS} src/main.cpp)

add_library(
    acutis_net
    socket_server.cpp
    address.cpp
    windows/socket_server_win.cpp
    windows/win_util.cpp
    windows/win_socket.cpp
    windows/win_server_socket.cpp)

target_include_directories(
    acutis_net
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(
    acutis_net
    PRIVATE ws2_32
            project_options
            project_warnings
            project_version
            CONAN_PKG::fmt
            CONAN_PKG::spdlog)

if(${ENABLE_TESTING})
    add_subdirectory(test)
endif()

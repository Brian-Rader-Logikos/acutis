add_executable(http_demo main.cpp)
target_link_libraries(
    http_demo
    PRIVATE project_options
            project_warnings
            project_version
            CONAN_PKG::docopt.cpp
            CONAN_PKG::fmt
            CONAN_PKG::spdlog)

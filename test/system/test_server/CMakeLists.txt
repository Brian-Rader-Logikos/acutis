add_executable(system_test_server main.cpp)

target_link_libraries(
    system_test_server 
    PRIVATE project_options
            project_warnings
            project_version
            CONAN_PKG::docopt.cpp
            CONAN_PKG::fmt
            CONAN_PKG::spdlog)

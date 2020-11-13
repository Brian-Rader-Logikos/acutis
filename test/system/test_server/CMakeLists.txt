add_executable(system_test_server main.cpp)

target_link_libraries(
    system_test_server
    PRIVATE acutis_net
            project_options
            project_warnings
            project_version
            CONAN_PKG::docopt.cpp
            CONAN_PKG::fmt
            CONAN_PKG::spdlog)

# Compile logging statements up to specified level Options:
#   TRACE(0), DEBUG(1), INFO(2), WARN(3), ERROR(4), CRITICAL(5), OFF(6)
# Default if not set: INFO(2)
target_compile_definitions(system_test_server PRIVATE $<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=1>)

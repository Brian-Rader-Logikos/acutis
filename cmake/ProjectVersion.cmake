configure_file("templates/project_version.h.in" "version/project_version.h")
add_library(project_version INTERFACE)
target_include_directories(project_version INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/version")

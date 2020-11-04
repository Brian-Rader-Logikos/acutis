add_subdirectory(test_server)

message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

find_package(Python3 COMPONENTS Interpreter)

add_test(
    NAME system_tests
    COMMAND Python3::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND_EXPAND_LISTS)

# Change to this when implementing real system tests. add_test(NAME system_tests COMMAND pytest
# --server_path=$<TARGET_FILE:system_test_server> --port=8089 COMMAND_EXPAND_LISTS)

add_subdirectory(test_server)

find_package(Python3 COMPONENTS Interpreter)

add_test(
    NAME system_tests
    COMMAND Python3::Interpreter -m pytest -rA ${CMAKE_CURRENT_SOURCE_DIR}
            --server_path=$<TARGET_FILE:system_test_server> --port=8089
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND_EXPAND_LISTS)

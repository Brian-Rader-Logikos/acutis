add_subdirectory(test_server)

add_test(NAME system_tests COMMAND python -m pytest WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND_EXPAND_LISTS)

# Change to this when implementing real system tests.
#add_test(NAME system_tests COMMAND pytest --server_path=$<TARGET_FILE:system_test_server> --port=8089 COMMAND_EXPAND_LISTS)

add_library(test_doubles stub_stream.cpp)

target_include_directories(test_doubles 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(test_doubles PRIVATE acutis_stream project_warnings project_options)

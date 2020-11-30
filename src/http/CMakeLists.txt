add_library(acutis_http parser.cpp method.cpp "uri.cpp")

target_include_directories(
    acutis_http
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(
    acutis_http
    PUBLIC acutis_stream
           project_options
           project_warnings
           project_version
           CONAN_PKG::fmt
           CONAN_PKG::spdlog)

if(${ENABLE_TESTING})
    add_subdirectory(test)
endif()

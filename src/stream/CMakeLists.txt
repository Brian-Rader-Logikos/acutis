add_library(acutis_stream stream.cpp)

target_include_directories(
    acutis_stream
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(
    acutis_stream
    PUBLIC project_options
           project_warnings
           project_version
           CONAN_PKG::fmt
           CONAN_PKG::spdlog)

if(${ENABLE_TESTING})
    add_subdirectory(test)
endif()

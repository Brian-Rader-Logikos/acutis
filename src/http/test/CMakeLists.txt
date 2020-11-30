# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

add_executable(test_unit_http test_parser.cpp)
target_link_libraries(
    test_unit_http
    PRIVATE acutis_http
            project_warnings
            project_options
            test_doubles
            catch_main)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to
# whatever you want, or use different for different binaries
catch_discover_tests(
    test_unit_http
    TEST_PREFIX
    "unittests."
    EXTRA_ARGS
    -s
    --reporter=xml
    --out=test_unit_http.result.xml)

cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

# add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest" "googletest")

project(ip_filter VERSION ${PROJECT_VESRION})

configure_file(lib/version_lib/version_define.h.in version_define.h)

add_executable(ip_filter src/main.cpp)
add_library(version lib/version_lib/version.cpp)
# add_executable(test_version test_version.cpp)

set_target_properties(ip_filter version PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    version
)
# target_link_libraries(test_version
# #    ${Boost_LIBRARIES}
#     gtest_main
#     version
# )

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(version PRIVATE
        /W4
    )
    # target_compile_options(test_version PRIVATE
    #     /W4
    # )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(test_version PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# enable_testing()

# add_test(test_version test_version)

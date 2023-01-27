cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest" "googletest" EXCLUDE_FROM_ALL)

project(ip_filter VERSION ${PROJECT_VESRION})

configure_file(lib/version_lib/version_define.h.in version_define.h)

add_executable(ip_filter src/main.cpp
    src/data_handler.h
    src/print.h
    src/read_input.h)

add_library(version lib/version_lib/version.cpp)
add_executable(ex_tests tests/tests.cpp)

set_target_properties(ip_filter version ex_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(ex_tests PRIVATE
    src/
)

target_link_libraries(ip_filter PRIVATE
    version
)

target_link_libraries(ex_tests
  #    ${Boost_LIBRARIES}
  gtest_main
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(version PRIVATE
        /W4
    )
    target_compile_options(ex_tests PRIVATE
      /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
   target_compile_options(ex_tests PRIVATE
       -Wall -Wextra -pedantic -Werror
   )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(ex_tests tests)

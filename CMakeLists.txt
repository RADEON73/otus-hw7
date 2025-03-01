cmake_minimum_required(VERSION 3.29)

project(bulk VERSION 1.0.0)

add_executable(bulk 
main.cpp
BulkProcessor.cpp BulkProcessor.h
Commands.h
CommandFactory.h
Outputters.h
)

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(bulk PRIVATE /W4)
else ()
    target_compile_options(bulk PRIVATE -Wall -Wextra -pedantic) 
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)




cmake_minimum_required(VERSION 4.3)
project(Gamma C)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# No messages about percent of compilation progress.
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

# Show commands that make uses.
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-pedantic -Werror -fstack-protector-strong -g")

set(SOURCE_FILES
    src/game_engine/find-union.h
    src/game_engine/find-union.c
    src/game_engine/gamma-struct.h
    src/game_engine/gamma-move.h
    src/game_engine/gamma-move.c
    src/game_engine/gamma.h
    src/game_engine/gamma.c
    src/UI/error-handling.h
    src/UI/error-handling.c
    src/UI/strings.h
    src/UI/strings.c
    src/UI/batch-mode.h
    src/UI/batch-mode.c
    src/UI/interactive-mode.h
    src/UI/interactive-mode.c
    src/gamma-launch.h
    src/gamma-launch.c
    src/gamma_main.c)

add_executable(gamma ${SOURCE_FILES})

set(TEST_SOURCE_FILES
    src/game_engine/find-union.h
    src/game_engine/find-union.c
    src/game_engine/gamma-struct.h
    src/game_engine/gamma-move.h
    src/game_engine/gamma-move.c
    src/game_engine/gamma.h
    src/game_engine/gamma.c
    src/UI/strings.h
    src/UI/strings.c
    src/gamma_test.c)

# Don't include `test` target in the `all` target for make.
add_executable(test EXCLUDE_FROM_ALL ${TEST_SOURCE_FILES})
set_target_properties(test PROPERTIES OUTPUT_NAME gamma_test)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Set location of configuration file and target location in the compilation
    # directory.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    # Dodajemy cel doc: użycie make doc spowoduje wywołanie doxygena z odpowiednim plikiem konfiguracyjnym w folderze kompilacji.
    # Add doc target: using make doc executes doxygen with a relevant
    # configuration file in the compilation directory.
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )
endif (DOXYGEN_FOUND)

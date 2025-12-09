cmake_minimum_required(VERSION 3.14)

project(Search VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_ASAN "Build with AddressSanitizer for tests" OFF)

if (ENABLE_ASAN)
	if (MSVC)
		add_compile_options(/fsanitize=address)
		add_link_options(/fsanitize=address)
	else()
		add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
		add_link_options(-fsanitize=address)
	endif()
endif()

# Search library providing data structures (ListSL, HashMap, BinarySearchTree)
file(GLOB SEARCH_SOURCES src/search/*.cpp)
file(GLOB SEARCH_HEADERS src/search/*.hpp src/search/*.h)
add_library(search ${SEARCH_SOURCES} ${SEARCH_HEADERS})
target_include_directories(search PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/search)
target_compile_features(search PUBLIC cxx_std_17)

# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Unit tests for search data structures
add_executable(test_search tests/test_search.cpp)
target_link_libraries(test_search PRIVATE search GTest::gtest_main)
add_test(NAME search_test COMMAND test_search)

# Search executable using src/main.cpp and the search library
add_executable(search_app src/main.cpp)
target_link_libraries(search_app PRIVATE search)

# Optional Valgrind memory checks (only on Unix and if valgrind is available)
if (UNIX)
	find_program(VALGRIND_EXECUTABLE valgrind)
	if (VALGRIND_EXECUTABLE)
		add_test(
			NAME memcheck_search
			COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --error-exitcode=1 $<TARGET_FILE:test_search>
		)
	endif()
endif()

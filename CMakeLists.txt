#cmake_minimum_required(VERSION 3.9)
#project(sample)

#set(CMAKE_CXX_STANDARD 11)

#add_executable(sample Sample/main.cpp Sample/hashtable.h Sample/hashtable.cpp)

cmake_minimum_required(VERSION 3.5)
project(TestSample LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

# Add local project module path so CMake includes custom CMake modules.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

include(CTest)
enable_testing()

add_library(hashtable
	Sample/hashtable.h
	Sample/hashtable.cpp
)
target_include_directories(hashtable
	PUBLIC
		Sample
)
target_compile_options(hashtable
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

add_executable(init_hashtable
	Sample/main.cpp
)

target_link_libraries(init_hashtable
	PRIVATE
		hashtable
)

target_compile_options(hashtable
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

#
# Create a library target for the Catch header-only test framework.
#
add_library(Catch INTERFACE)
target_include_directories(Catch
	INTERFACE
		tests/
)

#
# Create a target for executing the Catch unit tests.
#
add_executable(unit_tests
	tests/main.cpp
	tests/test1.cpp
)
target_include_directories(unit_tests
	PUBLIC
		tests/
)
target_link_libraries(unit_tests
	Catch
	hashtable
)
target_compile_options(unit_tests
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

# Load and use the .cmake file provided by Catch so all the test cases
# are made available to CTest.
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(unit_tests)

install(
	TARGETS unit_tests
	RUNTIME DESTINATION bin
)

set(CPACK_PACKAGE_NAME "Hello")
set(CPACK_PACKAGE_VENDOR "erichschroeter.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hello - CPack Component Installation Example")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Hello CPack Component Example")

# This must always be last!
include(CPack)

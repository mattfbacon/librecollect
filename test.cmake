set(DIR_TEST test)

set(test_sources
	Tests/behavior.cpp
	Tests/flush.cpp
	Tests/get_set_clear_has_delete.cpp
	Tests/handle.cpp
	Tests/increment_decrement.cpp
	Tests/instance.hpp
	Tests/prepend_append.cpp
	main.cpp
	)
list(TRANSFORM test_sources PREPEND ${DIR_TEST}/)

add_executable(tests ${test_sources})

find_package(Catch2 2 REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2 ${EXECUTABLE_NAME})

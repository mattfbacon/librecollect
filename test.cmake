set(DIR_TEST test)

set(test_sources
	main.cpp
	Tests/behavior.cpp
	Tests/flush.cpp
	Tests/get_set_clear_has_delete.cpp
	Tests/handle.cpp
	Tests/increment_decrement.cpp
	Tests/prepend_append.cpp
	)
list(TRANSFORM test_sources PREPEND ${${PROJECT_NAME}_SOURCE_DIR}/${DIR_TEST}/)
add_executable(test ${test_sources})

find_package(Catch2 2 REQUIRED)
target_link_libraries(test PRIVATE Catch2::Catch2 ${EXECUTABLE_NAME})
target_include_directories(test PRIVATE ${DIR_TEST})

set_property(TARGET test PROPERTY RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/${DIR_DIST}")
set_property(TARGET test PROPERTY LIBRARY_OUTPUT_DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/${DIR_DIST}")
set_property(TARGET test PROPERTY ARCHIVE_OUTPUT_DIRECTORY "${${PROJECT_NAME}_SOURCE_DIR}/${DIR_DIST}")

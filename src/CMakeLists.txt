file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SRC_FILES *.cpp)
message(WARNING ${HEADER_FILES})

set(OUTPUT "TheLightCorridor")
add_executable(${OUTPUT} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
set_target_properties(${OUTPUT} PROPERTIES
 	CXX_STANDARD 11
 	CXX_STANDARD_REQUIRED YES
 	CXX_EXTENSIONS NO
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set_target_properties(${OUTPUT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(${OUTPUT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_BIN_FOLDER})
set_target_properties(${OUTPUT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_BIN_FOLDER})
if (MSVC)
	target_compile_options(${OUTPUT} PRIVATE /W3)
else()
#	target_compile_options(${OUTPUT} PRIVATE -Wall -Wpedantic -pedantic-errors)
	target_compile_options(${OUTPUT} PRIVATE -Wall)
endif()

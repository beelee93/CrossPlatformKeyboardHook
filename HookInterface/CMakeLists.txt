cmake_minimum_required(VERSION 3.1)

project(HookInterface)

file(GLOB_RECURSE HookInterface_SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HookInterface_HEADER 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
	
add_library(HookInterface STATIC 
	${HookInterface_SRC}
	${HookInterface_HEADER}
	)
target_include_directories(HookInterface PUBLIC 
 "${CMAKE_CURRENT_SOURCE_DIR}/include" )
	
install( TARGETS HookInterface 
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include )
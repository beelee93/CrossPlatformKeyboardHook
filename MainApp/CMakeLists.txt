cmake_minimum_required(VERSION 3.1)

project(MainApp)

file(GLOB_RECURSE MainApp_SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE MainApp_HEADER 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h")
	
add_executable(MainApp  
	${MainApp_SRC} ${MainApp_HEADER})
target_link_libraries( MainApp HookInterface )
	
install( TARGETS MainApp	 
	RUNTIME DESTINATION bin )
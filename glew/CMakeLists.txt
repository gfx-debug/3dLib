project(glew)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DGLEW_STATIC)
set(
	src
	GL/glew.h
	GL/glxew.h
	GL/wglew.h
	glew.c
)

add_library(${PROJECT_NAME}  STATIC ${src})
target_link_libraries(${PROJECT_NAME} opengl32)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER 3dLib)
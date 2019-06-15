project(demo1)
add_definitions(-DORK_API=)
add_definitions(-DPROLAND_API=)
add_definitions(-DTIXML_USE_STL)
add_definitions(-DSTBI_NO_STDIO)
add_definitions(-DSTBI_NO_WRITE)
add_definitions(-DGLEW_STATIC)
set(
	SRC
	main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/proland/core)
include_directories(${CMAKE_SOURCE_DIR}/proland/ocean)
include_directories(${CMAKE_SOURCE_DIR}/proland/atmo)
include_directories(${CMAKE_SOURCE_DIR}/proland/forest)
include_directories(${CMAKE_SOURCE_DIR}/proland/terrain)
include_directories(${CMAKE_SOURCE_DIR}/proland/graph)
include_directories(${CMAKE_SOURCE_DIR}/proland/edit)
include_directories(${CMAKE_SOURCE_DIR}/proland/river)
add_executable(${PROJECT_NAME} ${SRC})
add_dependencies(${PROJECT_NAME} ork proland_core  proland_graph anttweakbar)
target_link_libraries(${PROJECT_NAME}  glew freeglut pthread ork proland_core  proland_graph anttweakbar)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "test")
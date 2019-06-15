project(ork)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -pedantic -Wall -ansi -Wno-long-long -fno-strict-aliasing")
endif()
add_definitions(-DORK_API=)
add_definitions(-DTIXML_USE_STL)
add_definitions(-DSTBI_NO_STDIO)
add_definitions(-DSTBI_NO_WRITE)
add_definitions(-DGLEW_STATIC)


file(GLOB core "ork/core/*.h" "ork/core/*.cpp")
file(GLOB math "ork/math/*.h" "ork/math/*.cpp")
file(GLOB render "ork/render/*.h" "ork/render/*.cpp")
file(GLOB resource "ork/resource/*.h" "ork/resource/*.cpp")
file(GLOB scenegraph "ork/scenegraph/*.h" "ork/scenegraph/*.cpp")
file(GLOB taskgraph "ork/taskgraph/*.h" "ork/taskgraph/*.cpp")
file(GLOB ui "ork/ui/*.h" "ork/ui/*.cpp")
file(GLOB util "ork/util/*.h" "ork/util/*.cpp")
file(GLOB libraries "libraries/*.h" "libraries/*.cpp" "libraries/stbi/*.h" "libraries/stbi/*.cpp" "libraries/tinyxml/*.h" "libraries/tinyxml/*.cpp")

source_group(core FILES ${core})
source_group(math FILES ${math})
source_group(render FILES ${render})
source_group(resource FILES ${resource})
source_group(scenegraph FILES ${scenegraph})
source_group(taskgraph FILES ${taskgraph})
source_group(ui FILES ${ui})
source_group(util FILES ${util})
source_group(libraries FILES ${libraries})

set(
	SRC
	${core}
	${math}
	${render}
    ${resource}
	${scenegraph}
    ${taskgraph}
	${ui}
	${util}
	${libraries}
)
add_library(${PROJECT_NAME}  STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} glew freeglut pthread)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "3dLib")

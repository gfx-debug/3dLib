set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(3dLib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_DEBUG_POSTFIX "d")
include_directories(${CMAKE_SOURCE_DIR}/ork3.1)
include_directories(${CMAKE_SOURCE_DIR}/ork3.1/libraries)
if (WIN32)
	include_directories(${CMAKE_SOURCE_DIR}/pthread)
	include_directories(${CMAKE_SOURCE_DIR}/glew)
	include_directories(${CMAKE_SOURCE_DIR}/freeglut-3.0.0/include)
	add_subdirectory(freeglut-3.0.0)
	add_subdirectory(pthread)
	add_subdirectory(glew)
endif()


set(
	ZLIB_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/zlib-1.2.11
)
ADD_SUBDIRECTORY(zlib-1.2.11)


set(
	LIBPNG_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/lpng1630
)
ADD_SUBDIRECTORY(lpng1630)


set(
	LIBJPEG_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/jpeg-9b
)
ADD_SUBDIRECTORY(jpeg-9b)




set(
	LIBTIFF_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/tiff-4.0.8
)
ADD_SUBDIRECTORY(tiff-4.0.8)

set(
	CURL_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/curl-7.54.1
)
ADD_SUBDIRECTORY(curl-7.54.1)

set(
	FREETYPE_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/freetype-2.8
)
ADD_SUBDIRECTORY(freetype-2.8)

set(
	GIFLIB_SOURCE_DIR
	${CMAKE_SOURCE_DIR}/giflib-5.1.4
)
ADD_SUBDIRECTORY(giflib-5.1.4)




add_subdirectory(ork3.1)
add_dependencies(ork  pthread glew freeglut )
ADD_SUBDIRECTORY(AntTweakBar)
add_subdirectory(proland)

add_subdirectory(test)
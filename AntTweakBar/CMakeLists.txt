cmake_minimum_required(VERSION 2.8)
project(anttweakbar)

SET(ANTTWEAKBAR_VERSION_MAJOR 1)
SET(ANTTWEAKBAR_VERSION_MINOR 16)
SET(ANTTWEAKBAR_VERSION "${ANTTWEAKBAR_VERSION_MAJOR}.${ANTTWEAKBAR_VERSION_MINOR}")

option(BUILD_SHARED_LIBS "shared build" ON)
set(CMAKE_DEBUG_POSTFIX "-gd")

file(GLOB ANT_SRC 
         # src/TwEventGLFW.c
          src/TwEventGLUT.c
         # src/TwEventSDL.c
         # src/TwEventSDL12.c
         # src/TwEventSDL13.c
          src/TwEventWin.c
        #   src/TwEventX11.c
          src/LoadOGL.cpp
          src/LoadOGLCore.cpp
          src/TwBar.cpp
          src/TwColors.cpp
          #src/TwDirect3D9.cpp
         # src/TwDirect3D10.cpp
          #src/TwDirect3D11.cpp
          src/TwEventSFML.cpp
          src/TwFonts.cpp
          src/TwMgr.cpp
          src/TwOpenGL.cpp
          src/TwOpenGLCore.cpp
          src/TwPrecomp.cpp)

if(UNIX)
    list(APPEND ANT_SRC src/TwEventX11.c)
endif(UNIX)

add_library(anttweakbar ${ANT_SRC})


if(BUILD_SHARED_LIBS AND MSVC)
  target_compile_definitions(anttweakbar PRIVATE -DTW_EXPORTS)
else(BUILD_SHARED_LIBS AND MSVC)
	target_compile_definitions(anttweakbar PUBLIC -DTW_STATIC)
endif(BUILD_SHARED_LIBS AND MSVC)
target_include_directories(anttweakbar PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(anttweakbar INTERFACE $<INSTALL_INTERFACE:include>)

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "cmake/anttweakbar")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/anttweakbar-config-version.cmake")
set(project_config "${generated_dir}/anttweakbar-config.cmake")
set(targets_export_name "anttweakbar-targets")
set(namespace "anttweakbar::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion VERSION ${ANTTWEAKBAR_VERSION}
)

configure_package_config_file(
    "config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)
install(FILES include/AntTweakBar.h DESTINATION include)
install(TARGETS anttweakbar 
    EXPORT anttweakbar-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)
install(EXPORT anttweakbar-targets 
	    NAMESPACE anttweakbar::
		DESTINATION cmake/anttweakbar)

set_property(TARGET anttweakbar PROPERTY FOLDER "3dLib")
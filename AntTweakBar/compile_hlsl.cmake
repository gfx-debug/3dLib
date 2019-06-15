find_program(FXC fxc PATHS "C:\\Program Files (x86)\\Windows Kits\\10\\bin\\x64" DOC "fx compiler")
if(NOT FXC)
    message(SEND_ERROR "Cannot find fxc.")
endif(NOT FXC)

set(FILE src/TwDirect3D11.hlsl)
get_filename_component(HLSL_PATH ${FILE} ABSOLUTE)

add_custom_command(TARGET anttweakbar PRE_BUILD
    COMMAND ${FXC} /Od /Zi /T vs_4_0_level_9_1 /E LineRectVS /Fh ${CMAKE_CURRENT_BINARY_DIR}/TwDirect3D11_LineRectVS.h ${HLSL_PATH}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "Effect-compile ${FILE}"
    VERBATIM)
add_custom_command(TARGET anttweakbar PRE_BUILD
    COMMAND ${FXC} /Od /Zi /T vs_4_0_level_9_1 /E LineRectCstColorVS /Fh ${CMAKE_CURRENT_BINARY_DIR}/TwDirect3D11_LineRectCstColorVS.h ${HLSL_PATH}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "Effect-compile ${FILE}"
    VERBATIM)
add_custom_command(TARGET anttweakbar PRE_BUILD
    COMMAND ${FXC} /Od /Zi /T ps_4_0_level_9_1 /E LineRectPS /Fh ${CMAKE_CURRENT_BINARY_DIR}/TwDirect3D11_LineRectPS.h ${HLSL_PATH}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "Effect-compile ${FILE}"
    VERBATIM)
add_custom_command(TARGET anttweakbar PRE_BUILD
    COMMAND ${FXC} /Od /Zi /T vs_4_0_level_9_1 /E TextVS /Fh ${CMAKE_CURRENT_BINARY_DIR}/TwDirect3D11_TextVS.h ${HLSL_PATH}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "Effect-compile ${FILE}"
    VERBATIM)
add_custom_command(TARGET anttweakbar PRE_BUILD
    COMMAND ${FXC} /Od /Zi /T vs_4_0_level_9_1 /E TextCstColorVS /Fh ${CMAKE_CURRENT_BINARY_DIR}/TwDirect3D11_TextCstColorVS.h ${HLSL_PATH}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "Effect-compile ${FILE}"
    VERBATIM)
add_custom_command(TARGET anttweakbar PRE_BUILD
    COMMAND ${FXC} /Od /Zi /T ps_4_0_level_9_1 /E TextPS /Fh ${CMAKE_CURRENT_BINARY_DIR}/TwDirect3D11_TextPS.h ${HLSL_PATH}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "Effect-compile ${FILE}"
    VERBATIM)


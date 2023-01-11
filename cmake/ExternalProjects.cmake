include(FetchContent)

#
# Fetch SFML
#

FetchContent_Declare(sfml
  URL https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-vc15-64-bit.zip
  FIND_PACKAGE_ARGS NAMES SFML sfml
)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
  FetchContent_Populate(sfml)
endif()

set(SFML_ROOT ${sfml_SOURCE_DIR})
include_directories(${sfml_SOURCE_DIR}/include)

#
# Fetch TGUI
#

FetchContent_Declare(TGUI
  URL https://github.com/texus/TGUI/releases/download/v0.9.5/TGUI-0.9.5-VisualStudio-64bit-for-SFML-2.5.1.zip
  FIND_PACKAGE_ARGS NAMES TGUI tgui
)

FetchContent_GetProperties(tgui)
if(NOT tgui_POPULATED)
  FetchContent_Populate(tgui)
endif()

set(TGUI_ROOT ${tgui_SOURCE_DIR})
include_directories(${tgui_SOURCE_DIR}/include)

#
# Fetch ecs.hpp
#

FetchContent_Declare(ecs.hpp
  GIT_REPOSITORY https://github.com/BlackMATov/ecs.hpp
  GIT_TAG main
)

#
# Fetch Google Test
#

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        71140c3ca7a87bb1b5b9c9f1500fea8858cce344 # Dec 23, 2022
  FIND_PACKAGE_ARGS NAMES GTest googletest
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#
# Register libraries
#

FetchContent_MakeAvailable(
  ecs.hpp
  googletest
)

include_directories(${ecs.hpp_SOURCE_DIR}/headers)

function(Win32CopyDlls PROJECT_NAME)
  if(WIN32)
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-system> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-window> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-audio> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command (TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:tgui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
  endif()
endfunction()

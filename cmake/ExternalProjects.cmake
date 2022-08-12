set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# Install ecs.hpp
set(ECS_PROJECT_NAME ecshpp)
ExternalProject_Add(${ECS_PROJECT_NAME}
  GIT_REPOSITORY https://github.com/BlackMATov/ecs.hpp
  GIT_TAG main

  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  INSTALL_COMMAND ""

  PREFIX ${EXTERNAL_INSTALL_LOCATION}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}

  # TEST_COMMAND ""
)

ExternalProject_Add_Step(${ECS_PROJECT_NAME}
  CopyHeaders
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXTERNAL_INSTALL_LOCATION}/src/${ECS_PROJECT_NAME}/headers ${EXTERNAL_INSTALL_LOCATION}/include
  DEPENDEES install
)

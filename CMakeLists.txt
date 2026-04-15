#  @file CMakeLists.txt
#  @author Gaspard Kirira
#
#  Copyright 2025, Gaspard Kirira. All rights reserved.
#  https://github.com/vixcpp/vix
#  Use of this source code is governed by a MIT license
#  that can be found in the License file.
#
#  @brief Vix AI Tensor module.
#
#  Small tensor module for Vix.
#  Provides basic tensor, device, engine, and version primitives.
#
#  Public targets:
#    - vix_ai_tensor
#    - vix::ai::tensor
#
#  Installation:
#    Installs headers, exported targets, and CMake package files
#    for find_package(vix_ai_tensor CONFIG REQUIRED).

cmake_minimum_required(VERSION 3.20)

project(vix_ai_tensor VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(VIX_AI_TENSOR_BUILD_TESTS "Build vix_ai_tensor tests" OFF)
option(VIX_AI_TENSOR_INSTALL "Install vix_ai_tensor targets" ON)
option(VIX_AI_TENSOR_WARNINGS "Enable extra warnings for vix_ai_tensor" ON)

add_library(vix_ai_tensor
  src/Version.cpp
  src/Tensor.cpp
  src/Device.cpp
  src/Engine.cpp
)

add_library(vix::ai::tensor ALIAS vix_ai_tensor)

target_include_directories(vix_ai_tensor
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(vix_ai_tensor PUBLIC cxx_std_20)

target_compile_definitions(vix_ai_tensor
  PUBLIC
    VIX_AI_TENSOR_VERSION="${PROJECT_VERSION}"
)

if(VIX_AI_TENSOR_WARNINGS)
  if(MSVC)
    target_compile_options(vix_ai_tensor PRIVATE /W4 /permissive-)
  else()
    target_compile_options(vix_ai_tensor PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Wconversion
      -Wshadow
    )
  endif()
endif()

if(TARGET vix_warnings)
  target_link_libraries(vix_ai_tensor PUBLIC vix_warnings)
endif()

if(VIX_ENABLE_SANITIZERS AND TARGET vix_sanitizers)
  target_link_libraries(vix_ai_tensor PUBLIC vix_sanitizers)
endif()

set_target_properties(vix_ai_tensor PROPERTIES
  OUTPUT_NAME vix_ai_tensor
  VERSION ${PROJECT_VERSION}
  SOVERSION 0
  EXPORT_NAME ai::tensor
)

if(VIX_AI_TENSOR_INSTALL)
  install(TARGETS vix_ai_tensor
    EXPORT vix_ai_tensorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
  )

  install(EXPORT vix_ai_tensorTargets
    FILE vix_ai_tensorTargets.cmake
    NAMESPACE vix::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vix_ai_tensor
  )

  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vix_ai_tensorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/vix_ai_tensor"
  )

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/vix_ai_tensor"
  )
endif()

if(VIX_AI_TENSOR_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif()

message(STATUS "vix::ai::tensor configured (${PROJECT_VERSION})")
message(STATUS "Include dir: ${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install: ${VIX_AI_TENSOR_INSTALL}")
message(STATUS "Tests: ${VIX_AI_TENSOR_BUILD_TESTS}")

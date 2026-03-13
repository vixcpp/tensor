cmake_minimum_required(VERSION 3.20)

project(tensor
  VERSION 0.1.0
  DESCRIPTION "Vix AI Tensor: tiny device/tensor/engine primitives"
  LANGUAGES CXX)

# ---- Options ---------------------------------------------------------------
option(VIX_AI_TENSOR_BUILD_TESTS "Build tensor tests" ON)
option(VIX_AI_TENSOR_INSTALL     "Install tensor targets" ON)
option(VIX_AI_TENSOR_WARNINGS    "Enable extra warnings" ON)

# ---- Library ----------------------------------------------------------------
add_library(vix_ai_tensor
  src/Version.cpp
  src/Tensor.cpp
  src/Device.cpp
  src/Engine.cpp
)

add_library(Vix::ai::tensor ALIAS vix_ai_tensor)

# Public headers
target_include_directories(vix_ai_tensor
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# C++ standard & version
target_compile_features(vix_ai_tensor PUBLIC cxx_std_20)
target_compile_definitions(vix_ai_tensor PUBLIC VIX_AI_TENSOR_VERSION="${PROJECT_VERSION}")

# Warnings
if(VIX_AI_TENSOR_WARNINGS)
  if(MSVC)
    target_compile_options(vix_ai_tensor PRIVATE /W4 /permissive-)
  else()
    target_compile_options(vix_ai_tensor PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
  endif()
endif()

# Good defaults
set_target_properties(vix_ai_tensor PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  VERSION   ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  EXPORT_NAME tensor
)

# ---- Install / package -----------------------------------------------------
if(VIX_AI_TENSOR_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)

  install(TARGETS vix_ai_tensor
    EXPORT vix_ai_tensorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  # Export targets for find_package()
  install(EXPORT vix_ai_tensorTargets
    FILE vix_ai_tensorTargets.cmake
    NAMESPACE Vix::AI::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vix_ai/tensor
  )

  # Config + version files
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfig.cmake
"include(\"\${CMAKE_CURRENT_LIST_DIR}/vix_ai_tensorTargets.cmake\")\n")

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/vix_ai_tensorConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vix_ai/tensor
  )
endif()

# ---- Tests -----------------------------------------------------------------
if(VIX_AI_TENSOR_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
  enable_testing()
  add_executable(vix_ai_tensor_smoke tests/smoke.cpp)
  target_link_libraries(vix_ai_tensor_smoke PRIVATE vix_ai_tensor)
  add_test(NAME smoke COMMAND vix_ai_tensor_smoke)
endif()

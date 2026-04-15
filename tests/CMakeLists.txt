cmake_minimum_required(VERSION 3.20)

#  @file test/CMakeLists.txt
#  @author Gaspard Kirira
#
#  Copyright 2025, Gaspard Kirira. All rights reserved.
#  https://github.com/vixcpp/vix
#  Use of this source code is governed by a MIT license
#  that can be found in the License file.
#
#  @brief Tests for the vix_ai_tensor module.
#
#  Minimal assert-based tests for the tensor module.
#  Each test is built as a small executable and registered with CTest.

add_executable(vix_ai_tensor_test_smoke
  smoke.cpp
)
target_link_libraries(vix_ai_tensor_test_smoke
  PRIVATE
    vix::ai::tensor
)
target_compile_features(vix_ai_tensor_test_smoke PRIVATE cxx_std_20)
add_test(NAME tensor_smoke COMMAND vix_ai_tensor_test_smoke)
set_tests_properties(tensor_smoke PROPERTIES LABELS "tensor;smoke")

add_executable(vix_ai_tensor_test_tensor
  tensor_tests.cpp
)
target_link_libraries(vix_ai_tensor_test_tensor
  PRIVATE
    vix::ai::tensor
)
target_compile_features(vix_ai_tensor_test_tensor PRIVATE cxx_std_20)
add_test(NAME tensor_tensor COMMAND vix_ai_tensor_test_tensor)
set_tests_properties(tensor_tensor PROPERTIES LABELS "tensor;core")

add_executable(vix_ai_tensor_test_device
  device_tests.cpp
)
target_link_libraries(vix_ai_tensor_test_device
  PRIVATE
    vix::ai::tensor
)
target_compile_features(vix_ai_tensor_test_device PRIVATE cxx_std_20)
add_test(NAME tensor_device COMMAND vix_ai_tensor_test_device)
set_tests_properties(tensor_device PROPERTIES LABELS "tensor;device")

add_executable(vix_ai_tensor_test_engine
  engine_tests.cpp
)
target_link_libraries(vix_ai_tensor_test_engine
  PRIVATE
    vix::ai::tensor
)
target_compile_features(vix_ai_tensor_test_engine PRIVATE cxx_std_20)
add_test(NAME tensor_engine COMMAND vix_ai_tensor_test_engine)
set_tests_properties(tensor_engine PROPERTIES LABELS "tensor;engine")

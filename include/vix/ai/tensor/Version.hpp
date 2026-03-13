/**
 * @file Version.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2025, Gaspard Kirira. All rights reserved.
 * https://github.com/vixcpp/vix
 * Use of this source code is governed by a MIT license that can be found in the License file.
 *
 * Vix.cpp
 */
#ifndef VIX_AI_TENSOR_VERSION_HPP
#define VIX_AI_TENSOR_VERSION_HPP

namespace vix::ai::tensor
{
  inline constexpr const char *version() noexcept
  {
#ifdef VIX_AI_VERSION
    return VIX_AI_VERSION;
#else
    return "0.1.0";
#endif
  }

} // namespace vix::ai::tensor

#endif

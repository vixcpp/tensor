/**
 * @file Engine.hpp
 * @author Gaspard Kirira
 *
 * Copyright 2025, Gaspard Kirira. All rights reserved.
 * https://github.com/vixcpp/vix
 * Use of this source code is governed by a MIT license that can be found in the License file.
 *
 * Vix.cpp
 */
#ifndef VIX_AI_TENSOR_ENGINE_HPP
#define VIX_AI_TENSOR_ENGINE_HPP

#include <string>
#include <memory>
#include <numeric>

#include <vix/ai/tensor/Tensor.hpp>
#include <vix/ai/tensor/Device.hpp>

namespace vix::ai::tensor
{
  class Engine
  {
  public:
    Engine() = default;
    explicit Engine(Device dev) : device_(std::move(dev)) {}

    const Device &device() const noexcept { return device_; }

    std::string compute(const Tensor &t) const
    {
      float sum = std::accumulate(t.data().begin(), t.data().end(), 0.0f);
      return std::string{"Engine["} + device().name() + "] rank=" +
             std::to_string(t.rank()) + " numel=" + std::to_string(t.numel()) +
             " sum=" + std::to_string(sum);
    }

    std::string info() const
    {
      return std::string{"vix-ai-tensor Engine on "} + device().name();
    }

  private:
    Device device_{};
  };

} // namespace vix::ai::tensor

#endif // VIX_AI_TENSOR_ENGINE_HPP

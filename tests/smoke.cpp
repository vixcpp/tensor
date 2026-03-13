#include <cassert>
#include <iostream>
#include <vix/ai/tensor/Version.hpp>
#include <vix/ai/tensor/Engine.hpp>
#include <vix/ai/tensor/Tensor.hpp>

using namespace vix::ai::tensor;

int main()
{
  std::cout << "vix-ai-tensor version: " << version() << "\n";
  Tensor t({2, 2});
  Engine e{Device::from_string("cpu")};
  auto msg = e.compute(t);
  std::cout << msg << "\n";
  assert(t.rank() == 2);
  return 0;
}

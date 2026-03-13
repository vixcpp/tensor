#include <cassert>
#include <vix/ai/tensor/Tensor.hpp>

using namespace vix::ai::tensor;

int main()
{
  Tensor a({3, 3});
  assert(a.rank() == 2);
  assert(a.numel() == 9);

  a.fill(1.0f);
  float sum = 0.f;
  for (float v : a.data())
    sum += v;
  assert(sum == 9.0f);
  (void)sum;

  a.reshape({1, 9});
  assert(a.rank() == 2);
  assert(a.numel() == 9);

  auto b = Tensor::zeros({2, 2, 2});
  assert(b.numel() == 8);
  for (float v : b.data())
  {
    assert(v == 0.0f);
    (void)v;
  }

  auto c = Tensor::ones({2, 2});
  float total = 0.f;
  for (float v : c.data())
    total += v;
  assert(total == 4.0f);
  (void)total;

  return 0;
}

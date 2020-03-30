// Just a silly benchmark to demonstrate how to use GoogleBenchmark

#include <benchmark/benchmark.h>
#include "CPPLib/CPPLib.hpp"
#include <random>
#include <vector>
#include <algorithm>

constexpr int low_bound = 0;
constexpr int up_bound = 100000;
constexpr int seed = 1;

// Demonstrate how to use fixtures
template <typename T>
class MyFixture : public benchmark::Fixture
{
  public:
    std::vector<T> input;
    std::default_random_engine dre;        // engine
    std::uniform_int_distribution<int> di; // distribution

    void SetUp(const ::benchmark::State& state)
    {
        dre = std::default_random_engine(seed);
        di = std::uniform_int_distribution<int>(low_bound, up_bound);
    }

    void RandomInput(int n = 100000)
    {
        input.resize(n);
        std::generate(input.begin(), input.end(), [&] { return static_cast<T>(di(dre)); });
    }
};

BENCHMARK_TEMPLATE_DEFINE_F(MyFixture, BM_DoubleVec, double)
(benchmark::State& st)
{
    RandomInput();
    auto scalar = 2.0;
    for (auto _ : st)
    {
        auto output = CPPLib::MultiplyByScalar(input, scalar);
        benchmark::DoNotOptimize(output.data());
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(MyFixture, BM_DoubleInt, int)
(benchmark::State& st)
{
    RandomInput();
    auto scalar = 2;
    for (auto _ : st)
    {
        auto output = CPPLib::MultiplyByScalar(input, scalar);
        benchmark::DoNotOptimize(output.data());
    }
}

// Define another benchmark
static void BM_Hello(benchmark::State& state)
{
    std::string input = "Jeremy";
    for (auto _ : state)
    {
        auto output = CPPLib::Hello(input);
    }
}

// Benchmark automatically registered
BENCHMARK(BM_Hello)->Unit(benchmark::kNanosecond);

// Manual registration required because used DEFINE_F
BENCHMARK_REGISTER_F(MyFixture, BM_DoubleVec)->Unit(benchmark::kMicrosecond);
BENCHMARK_REGISTER_F(MyFixture, BM_DoubleInt)->Unit(benchmark::kMicrosecond);
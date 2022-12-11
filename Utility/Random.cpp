#include "Random.hpp"

namespace util
{
    Random::Random(uint32_t seed = 517)
    {
        SetSeed(seed);
    }

    void Random::SetSeed(uint32_t seed)
    {
        a = seed = 1812433253u * (seed ^ (seed >> 30));
        b = seed = 1812433253u * (seed ^ (seed >> 30)) + 1;
        c = seed = 1812433253u * (seed ^ (seed >> 30)) + 2;
        d = seed = 1812433253u * (seed ^ (seed >> 30)) + 3;
    }

    uint32_t Random::operator()() {
        uint32_t t = (a ^ (a << 11));
        a = b;
        b = c;
        c = d;
        return d = (d ^ (d >> 19)) ^ (t ^ (t >> 8));
    }

    uint32_t Random::operator()(int MAX)
    {
        return (uint64_t) operator()() * MAX >> 32;
    }

    uint32_t Random::operator()(int L, int R)
    {
        return L + operator()(R - L);
    }

    double Random::Double()
    {
        return static_cast<double>(operator()()) / (1LL << 32);
    }

    bool Random::Prob(const double p)
    {
        return (uint32_t)(p * (1LL << 32)) > operator()();
    }
}
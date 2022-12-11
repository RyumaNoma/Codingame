#include <cstdint>

namespace util
{
    class Random
    {
    private:
        uint32_t a, b, c, d;

    public:
        Random(uint32_t seed = 517);

        void SetSeed(uint32_t seed);
        uint32_t operator()();

        // [0,MAX)
        uint32_t operator()(int MAX);

        // [L,R)
        uint32_t operator()(int L, int R);

        // [0,1) の実数
        double Double();

        // 確率 p で true を返す
        bool Prob(const double p);
    };
}
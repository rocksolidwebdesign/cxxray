#ifndef CXXRAY_RAND_H
#define CXXRAY_RAND_H

#include <random>
#include <vector>

namespace CxxRay {

template<typename ValT>
struct RandReal
{
    using DeviceT = std::random_device;
    using GenT = std::mt19937;
    using DistT = std::uniform_real_distribution<ValT>;

    DeviceT rd;
    GenT gen;
    DistT dis;

    RandReal(ValT const lbound, ValT const ubound)
        : rd{}
        , gen{rd()}
        , dis{lbound, ubound}
    {
    }

    RandReal()
        : rd{}
        , gen{rd()}
        , dis{}
    {
    }
};

template<typename ValT>
struct RandInt
{
    using DeviceT = std::random_device;
    using GenT = std::mt19937;
    using DistT = std::uniform_int_distribution<ValT>;

    DeviceT rd;
    GenT gen;
    DistT dis;

    RandInt(ValT const lbound, ValT const ubound)
        : rd{}
        , gen{rd()}
        , dis{lbound, ubound}
    {
    }

    RandInt()
        : rd{}
        , gen{rd()}
        , dis{}
    {
    }
};

struct RandByte
{
    RandInt<short> rand;

    RandByte()
        : rand{0, 255}
    {
    }
};

template<typename T>
T get(RandReal<T> & r)
{
    return r.dis(r.gen);
}

template<typename T>
T get(RandInt<T> & r)
{
    return r.dis(r.gen);
}

unsigned char
get(RandByte & b)
{
    auto & r = b.rand;

    return r.dis(r.gen);
}

template<typename T>
std::vector<T>
series(
    RandReal<T> & r,
    long const qty)
{
    std::vector<T> out = {};
    out.reserve(qty);

    for (long i = 0; i < qty; i++) {
        out.push_back(r.dis(r.gen));
    }

    return out;
}

template<typename T>
std::vector<T>
series(
    RandInt<T> & r,
    long const qty)
{
    std::vector<T> out = {};
    out.reserve(qty);

    for (long i = 0; i < qty; i++) {
        out.push_back(r.dis(r.gen));
    }

    return out;
}

inline
std::vector<unsigned char>
series(
    RandByte & b,
    long const qty)
{
    auto & r = b.rand;

    std::vector<unsigned char> out = {};
    out.reserve(qty);

    for (long i = 0; i < qty; i++) {
        out.push_back(static_cast<unsigned char>(r.dis(r.gen)));
    }

    return out;
}

} // namespace CxxRay

#endif

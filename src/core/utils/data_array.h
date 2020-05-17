#ifndef CXXRAY_DATA_ARRAY_H
#define CXXRAY_DATA_ARRAY_H

#include <memory>
#include <cstdlib>

namespace CxxRay {

template<typename T>
T* allocateDataArray(long length)
{
    return (T*)std::malloc(length * sizeof(T));
}

template<typename T>
struct DataArrayDeleter
{
    void operator()(T * ptr)
    {
        std::free(ptr);
    }
};

template<typename T>
struct DataArray
{
    using GuardT = std::unique_ptr<T,DataArrayDeleter<T>>;
    using DataT = T*;

    long len;
    GuardT guard;
    DataT data;

    DataArray(T* dat, long l)
        : len{l}
        , guard{dat}
        , data{dat}
    {
    }

    DataArray(long l)
        : len{l}
        , guard{nullptr}
        , data{nullptr}
    {
        guard.reset(allocateDataArray<T>(l));
        data = guard.get();
    }

    DataArray()
        : DataArray(1)
    {
    }

    void reallocate()
    {
        guard.reset(allocateDataArray<T>(len));
    }

    void reallocate(long l)
    {
        guard.reset(allocateDataArray<T>(l));

        len = l;
    }
};

}

#endif

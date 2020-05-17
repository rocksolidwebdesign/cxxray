#include "utils/data_array.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace CxxRay {

int testDataArrayMain()
{
    namespace fs = std::filesystem;

    DataArray<int> x(10);

    return 0;
}

} // namespace CxxRay

int main()
{
    return CxxRay::testDataArrayMain();
}

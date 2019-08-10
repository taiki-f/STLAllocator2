#include "STL.hpp"
#include <iostream>

int main()
{
    {
        drs::stl::vector<int> vec;
        vec.reserve(2);
        vec.push_back(50);
        vec.push_back(55);
        vec.push_back(100);
        vec.push_back(150);
        vec.push_back(200);

        for (auto& v : vec)
        {
            std::cout << v << std::endl;
        }
    }

    return 0;
}

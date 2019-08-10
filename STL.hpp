#pragma once

#include "Types.h"
#include "STLAllocator.hpp"
#include <vector>
#include <list>

namespace drs { namespace stl
{
    /// <summary>
    /// 自作vector
    /// </summary>
    template<typename T> 
    using vector = std::vector<T, mem::STLAllocator<T>>;

    /// <summary>
    /// 自作list
    /// </summary>
    template<typename T>
    using list = std::list<T, mem::STLAllocator<T>>;
} }

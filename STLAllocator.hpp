#pragma once

#include "Types.h"
#include "Memory.hpp"

namespace drs { namespace mem
{
    /// <summary>
    /// STL用のアロケーター
    /// </summary>
    template<class T>
    struct STLAllocator
    {
        using value_type = T;

        /// <summary>
        /// デフォルトコンストラクタ
        /// </summary>
        STLAllocator() = default;

        /// <summary>
        /// コピーコンストラクタ
        /// </summary>
        STLAllocator(const T&) {}

        /// <summary>
        /// コピーコンストラクタ
        /// </summary>
        template<class U>
        STLAllocator(const U&) {}

        /// <summary>
        /// アロケーター
        /// </summary>
        /// <param name="num">確保するバイト数</param>
        /// <returns>確保したメモリ領域のポインタ</returns>
        T* allocate(size_t num) {
            size_t size = sizeof(T) * num;
            return static_cast<T*>(Malloc(size));
        }

        /// <summary>
        /// デアロケーター
        /// </summary>
        /// <param name="p">開放するメモリ領域</param>
        /// <param name="num">ブロック数</param>
        void deallocate(T* p, size_t num) {
            Free(p);
        }
    };

    /// <summary>
    /// 比較関数
    /// </summary>
    template<class T, class U>
    bool operator==(const STLAllocator<T>& lhs, const STLAllocator<U>& rhs)
    {
        return true;
    }

    /// <summary>
    /// 比較関数
    /// </summary>
    template<class T, class U>
    bool operator!=(const STLAllocator<T>& lhs, const STLAllocator<U>& rhs)
    {
        return false;
    }
} }

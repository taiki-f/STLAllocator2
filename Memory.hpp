#pragma once

#include <stdlib.h>
#include "Types.h"

namespace drs { namespace mem
{
    /// <summary>
    /// メモリを確保する
    /// </summary>
    /// <param name="size">確保するメモリのバイト数</param>
    /// <returns>確保したメモリを返す</returns>
    void* Malloc(size_t size);

    /// <summary>
    /// メモリを開放する
    /// </summary>
    /// <param name="p">開放対象のメモリ空間</param>
    void Free(void* p);
} }

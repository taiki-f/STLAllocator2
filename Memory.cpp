#include "Memory.hpp"
#include <algorithm>
#include <vector>
#include <assert.h>

namespace
{
    /// <summary>
    /// アロケーター情報
    /// </summary>
    struct AllocatorInfo
    {
        int     id;         // アロケーターID
        void*   data;       // データのポインタ
        size_t  dataSize;   // データサイズ
    };

    // アロケーター情報バッファ
    std::vector<AllocatorInfo> allocatorInfoBuffer;

    // アロケーターのID管理
    static DWord allocatelId = 0;

    /// <summary>
    /// アロケーターのIDを返す
    /// </summary>
    /// <returns></returns>
    DWord GetAllocatelId()
    {
        assert(allocatelId < (allocatelId + 1));
        return (++allocatelId) % 0xffffffff;
    }
}

namespace drs { namespace mem
{
    /// <summary>
    /// メモリを確保する
    /// </summary>
    void* Malloc(size_t size)
    {
        AllocatorInfo info;
        info.id = GetAllocatelId();
        info.data = ::malloc(size);
        info.dataSize = size;

        // バッファに情報を登録
        allocatorInfoBuffer.push_back(info);
        return info.data;
    }

    /// <summary>
    /// メモリを開放する
    /// </summary>
    void Free(void* p)
    {
        auto it = std::find_if(
                    std::cbegin(allocatorInfoBuffer), 
                    std::cend(allocatorInfoBuffer),
                    [&](const AllocatorInfo& i) {
                        return (p == i.data);
                    });

        // 想定された処理を経由して取得したメモリか確認する
        assert(it != std::cend(allocatorInfoBuffer));

        // バッファを解放
        ::free(it->data);

        // バッファの情報を破棄
        allocatorInfoBuffer.erase(it);
    }
} }

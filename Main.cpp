#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <assert.h>

namespace drs
{
    // アロケーターのID管理
    static unsigned int allocatelId = 0;
    unsigned int GetAllocatelId() {
        assert(allocatelId < (allocatelId + 1));
        return ++allocatelId;
    }

    // バッファ構造体
    struct Buffer {
        int         id;         // アロケーターバッファ
        void*       data;       // データのポインタ
        std::size_t dataSize;   // データサイズ
    };

    // アロケーターバッファ
    std::vector<Buffer> allocateBuffer;

    // 自作malloc
    void* malloc(std::size_t size)
    {
        // バッファ情報を準備
        Buffer buffer;
        buffer.id = GetAllocatelId();
        buffer.data = ::malloc(size);
        buffer.dataSize = size;

        // バッファ情報を登録
        allocateBuffer.push_back(buffer);
        return buffer.data;
    }

    // 自作free
    void free(void* p)
    {
        // 該当のバッファを探す
        auto it = std::find_if(
            std::cbegin(allocateBuffer),
            std::cend(allocateBuffer),
            [&](const Buffer& buffer) {
                return (buffer.data == p);
            });
        assert(it != std::cend(allocateBuffer));

        // バッファの解放
        ::free(it->data);

        // バッファ情報を破棄
        allocateBuffer.erase(it);
    }

    /// <summary>
    /// 自作アロケーター
    /// </summary>
    template<class T>
    struct STLAllocator
    {
        using value_type = T;

        // デフォルトコンストラクタ
        STLAllocator() = default;

        // コピーコンストラクタ
        STLAllocator(const T&) {}

        // コピーコンストラクタ
        template<class U>
        STLAllocator(const U&) {}

        // メモリの確保
        T* allocate(std::size_t num)
        {
            std::size_t size = sizeof(T) * num;
            return static_cast<T*>(drs::malloc(size));
        }

        // メモリの開放
        void deallocate(T* p, std::size_t num)
        {
            drs::free(p);
        }
    };

    template<class T, class U>
    bool operator==(const STLAllocator<T>& lhs, const STLAllocator<U>& rhs)
    {
        return true;
    }

    template<class T, class U>
    bool operator!=(const STLAllocator<T>& lhs, const STLAllocator<U>& rhs)
    {
        return false;
    }

    // 自作アロケーターを使ったSTL
    template<typename T> using vector = std::vector<T, STLAllocator<T>>;
    template<typename T> using list = std::list<T, STLAllocator<T>>;
}

int main()
{
    {
        drs::vector<int> vec;
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

        int i = 100;
    }

    return 0;
}

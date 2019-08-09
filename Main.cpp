#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <assert.h>

namespace drs
{
    // �A���P�[�^�[��ID�Ǘ�
    static unsigned int allocatelId = 0;
    unsigned int GetAllocatelId() {
        assert(allocatelId < (allocatelId + 1));
        return ++allocatelId;
    }

    // �o�b�t�@�\����
    struct Buffer {
        int         id;         // �A���P�[�^�[�o�b�t�@
        void*       data;       // �f�[�^�̃|�C���^
        std::size_t dataSize;   // �f�[�^�T�C�Y
    };

    // �A���P�[�^�[�o�b�t�@
    std::vector<Buffer> allocateBuffer;

    // ����malloc
    void* malloc(std::size_t size)
    {
        // �o�b�t�@��������
        Buffer buffer;
        buffer.id = GetAllocatelId();
        buffer.data = ::malloc(size);
        buffer.dataSize = size;

        // �o�b�t�@����o�^
        allocateBuffer.push_back(buffer);
        return buffer.data;
    }

    // ����free
    void free(void* p)
    {
        // �Y���̃o�b�t�@��T��
        auto it = std::find_if(
            std::cbegin(allocateBuffer),
            std::cend(allocateBuffer),
            [&](const Buffer& buffer) {
                return (buffer.data == p);
            });
        assert(it != std::cend(allocateBuffer));

        // �o�b�t�@�̉��
        ::free(it->data);

        // �o�b�t�@����j��
        allocateBuffer.erase(it);
    }

    /// <summary>
    /// ����A���P�[�^�[
    /// </summary>
    template<class T>
    struct STLAllocator
    {
        using value_type = T;

        // �f�t�H���g�R���X�g���N�^
        STLAllocator() = default;

        // �R�s�[�R���X�g���N�^
        STLAllocator(const T&) {}

        // �R�s�[�R���X�g���N�^
        template<class U>
        STLAllocator(const U&) {}

        // �������̊m��
        T* allocate(std::size_t num)
        {
            std::size_t size = sizeof(T) * num;
            return static_cast<T*>(drs::malloc(size));
        }

        // �������̊J��
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

    // ����A���P�[�^�[���g����STL
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

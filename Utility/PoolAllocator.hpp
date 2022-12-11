#include <cstdint>
#include <iostream>

namespace util
{
    template<class ObjectType> class PoolAllocator;
    template<class ObjectType> std::ostream& operator<<(std::ostream& os, const PoolAllocator<ObjectType>& allocator);

    // 
    /*
    ref: https://github.com/mtrebi/memory-allocators#pool-allocator
    初期化　　O(N)
    割り付け　O(1)
    解放　　　O(1)
    */
    template <class ObjectType>
    class PoolAllocator
    {
    protected:
        union block_t
        {
            ObjectType block;
            union block_t* next;
            block_t() {}
        };
        using Block = union block_t;
        
        const size_t num_blocks_;
        Block* blocks_;
        Block* top_;
        size_t num_allocated_;
    public:
        // O(N)
        // 領域の確保
        PoolAllocator(size_t num_blocks);

        ~PoolAllocator();

        // O(N)
        // 初期化する
        // 割り付けされているブロックをすべて解放する
        void Init();

        // O(1)
        // 領域の割り付け
        // 失敗したらnullptrを返す
        ObjectType* Allocate();

        // O(1)
        // 領域の解放
        // 不正なアドレスが渡された場合は未定義
        void Free(ObjectType* block);

        // O(1)
        // 割り付けされているブロックの数
        size_t AllocatedBlocks() const;

        friend std::ostream& operator<< <ObjectType>(std::ostream& os, const PoolAllocator<ObjectType>& allocator);
    };
}

namespace util
{
    template<class ObjectType>
    PoolAllocator<ObjectType>::PoolAllocator(size_t num_blocks)
        : num_blocks_(num_blocks)
        , blocks_(new Block[num_blocks])
        , top_(&blocks_[0])
        , num_allocated_(0)
    {
        Init();
    }

    template<class ObjectType>
    PoolAllocator<ObjectType>::~PoolAllocator()
    {
        delete[] blocks_;
    }

    template<class ObjectType>
    void PoolAllocator<ObjectType>::Init()
    {
        for (int i = 0; i < num_blocks_ - 1; ++i)
        {
            blocks_[i].next = &blocks_[i + 1];
        }
        blocks_[num_blocks_ - 1].next = nullptr;

        top_ = &blocks_[0];
        num_allocated_ = 0;
    }

    template<class ObjectType>
    ObjectType* PoolAllocator<ObjectType>::Allocate()
    {
        // 未使用のブロックが存在しない場合
        if (top_ == nullptr)
        {
            return nullptr;
        }

        ObjectType* r = &top_->block;
        top_ = top_->next;
        num_allocated_ += 1;

        return r;
    }

    template<class ObjectType>
    void PoolAllocator<ObjectType>::Free(ObjectType* block)
    {
        if (block == nullptr) return;

        reinterpret_cast<Block*>(block)->next = top_;
        top_ = reinterpret_cast<Block*>(block);
        num_allocated_ -= 1;
    }

    template<class ObjectType>
    size_t PoolAllocator<ObjectType>::AllocatedBlocks() const
    {
        return num_allocated_;
    }

    template<class ObjectType>
    std::ostream& operator<<(std::ostream& os, const PoolAllocator<ObjectType>& allocator)
    {
        os << "Number of blocks: " << allocator.num_blocks_
            << "Block Size: " << sizeof(ObjectType) << "[byte]"
            << "Allocated blocks: " << allocator.AllocatedBlocks();
        return os;
    }
}
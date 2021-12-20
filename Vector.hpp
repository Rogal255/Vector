#pragma once
#include <memory>

namespace pr {

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    void push_back(T&& value) {
        if (size_ == capacity_) {
            reallocate();
        }
        *(front_ + size_++) = value;
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            reallocate();
        }
        std::construct_at(front_ + size_++, std::forward<Args>(args)...);
    }

    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] std::size_t capacity() const { return capacity_; }

private:
    Allocator alloc_;
    std::size_t size_ {0};
    std::size_t capacity_ {0};
    T* front_ {nullptr};

    void reallocate() {
        if (front_) {
            capacity_ = size_ * 2;
            T* tmpPtr = alloc_.allocate(capacity_);
            for (std::size_t i {0}; i < size_; ++i) {
                *(tmpPtr + i) = *(front_ + i);
            }
            std::destroy_n(front_, size_);
            alloc_.deallocate(front_, size_);
            front_ = tmpPtr;
        } else {
            capacity_ = 1;
            front_ = alloc_.allocate(capacity_);
        }
    }
};

}

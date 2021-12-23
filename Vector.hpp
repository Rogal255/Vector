#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace pr {

template <typename Type>
using remove_cv_ref = std::remove_cv_t<std::remove_reference_t<Type>>;

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    ~Vector() {
        if (front_) {
            std::destroy_n(front_, size_);
            alloc_.deallocate(front_, capacity_);
        }
    }

    void reserve(std::size_t newCapacity) {
        if (capacity_ < newCapacity) {
            reallocate(newCapacity);
        }
    }

    void shrink_to_fit() {
        if (capacity_ > size_) {
            reallocate(size_);
        }
    }

    template <typename U>
    void push_back(U&& value) {
        static_assert(std::is_same_v<remove_cv_ref<T>, remove_cv_ref<U>>);
        reallocateIfNeeded();
        std::allocator_traits<Allocator>::construct(alloc_, front_ + size_++, std::forward<U>(value));
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        reallocateIfNeeded();
        std::allocator_traits<Allocator>::construct(alloc_, front_ + size_, std::forward<Args>(args)...);
        return *(front_ + size_++);
    }

    T& operator[](std::size_t index) { return *(front_ + index); }
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("pr::Vector::at method");
        }
        return operator[](index);
    }

    [[nodiscard]] T* data() { return front_; }
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] std::size_t capacity() const { return capacity_; }

private:
    Allocator alloc_;
    std::size_t size_ {0};
    std::size_t capacity_ {0};
    T* front_ {nullptr};

    void reallocateIfNeeded() {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                reallocate(1);
            } else {
                reallocate(capacity_ * 2);
            }
        }
    }

    void reallocate(std::size_t newCapacity) {
        if (front_) {
            T* tmpPtr = alloc_.allocate(newCapacity);
            for (std::size_t i {0}; i < size_; ++i) {
                *(tmpPtr + i) = std::move(*(front_ + i));
            }
            std::destroy_n(front_, size_);
            alloc_.deallocate(front_, capacity_);
            front_ = tmpPtr;
        } else {
            front_ = alloc_.allocate(newCapacity);
        }
        capacity_ = newCapacity;
    }
};

}

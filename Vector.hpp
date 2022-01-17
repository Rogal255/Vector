#pragma once
#include "Helpers.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace pr {

template <typename T, typename U>
concept SameType = std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

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
    void push_back(U&& value) requires SameType<T, U> {
        reallocateIfNeeded();
        std::allocator_traits<Allocator>::construct(alloc_, front_ + size_++, std::forward<U>(value));
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        reallocateIfNeeded();
        std::allocator_traits<Allocator>::construct(alloc_, front_ + size_, std::forward<Args>(args)...);
        return *(front_ + size_++);
    }

    T& operator[](std::size_t index) noexcept { return *(front_ + index); }
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("pr::Vector::at method");
        }
        return operator[](index);
    }

    [[nodiscard]] T* data() noexcept { return front_; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }

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

template <typename Allocator>
class Vector<bool, Allocator> {
public:
    void reserve(std::size_t newCapacity) {
        if (vec_.capacity() < (newCapacity / 8) + 1) {
            vec_.reserve((newCapacity / 8) + 1);
        }
    }

    void shrink_to_fit() { vec_.shrink_to_fit(); }

    void push_back(const bool& value) {
        if (++size_ > (vec_.size() * 8)) {
            uint8_t newElement = static_cast<uint8_t>(value) << 0;
            vec_.push_back(newElement);
            return;
        }
        if (value) {
            vec_[size_ / 8] |= 1 << size_ % 8;
        } else {
            vec_[size_ / 8] &= 0 << size_ % 8;
        }
    }

    boolReference operator[](std::size_t index) noexcept { return boolReference(vec_[index / 8], index % 8); }
    boolReference at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("pr::Vector::at method");
        }
        return operator[](index);
    }

private:
    Vector<uint8_t, Allocator> vec_;
    std::size_t size_ {0};
};

}

#include "Vector.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(Vector, CapacityIncreaseTest) {
    pr::Vector<int> vec;
    constexpr std::size_t iterations {10000};
    ASSERT_EQ(vec.capacity(), 0);
    std::size_t lastReallocation {0};
    for (std::size_t i {0}; i < iterations; ++i) {
        ASSERT_EQ(vec.size(), i);
        if (vec.size() == 1) {
            ASSERT_EQ(vec.capacity(), 1);
        }
        if (vec.size() == vec.capacity()) {
            if (lastReallocation != 0) {
                ASSERT_EQ(vec.size(), lastReallocation * 2);
            }
            lastReallocation = vec.size();
        }
        vec.push_back(1);
    }
}

TEST(Vector, push_back) {
    pr::Vector<std::size_t> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
        ASSERT_EQ(vec[i], i);
        ASSERT_EQ(vec.at(i), i);
    }
}

TEST(Vector, subscriptOperator) {
    pr::Vector<std::size_t> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
        ASSERT_EQ(vec[i], i);
    }
}

TEST(Vector, at) {
    pr::Vector<std::size_t> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
        ASSERT_EQ(vec.at(i), i);
        ASSERT_THROW(vec.at(i + 1), std::out_of_range);
    }
    ASSERT_NO_THROW(vec.at(iterations - 1));
    ASSERT_THROW(vec.at(iterations), std::out_of_range);
}

TEST(Vector, reallocationTest) {
    pr::Vector<std::size_t> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
    }
    for (std::size_t i {0}; i < iterations; ++i) {
        ASSERT_EQ(vec[i], i);
        ASSERT_EQ(vec.at(i), i);
    }
}


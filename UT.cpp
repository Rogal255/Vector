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

TEST(Vector, reserveTest) {
    pr::Vector<std::size_t> vec;
    ASSERT_EQ(vec.capacity(), 0);
    constexpr std::size_t iterations {99};
    vec.reserve(iterations + 1);
    ASSERT_EQ(vec.capacity(), iterations + 1);
    vec.push_back(static_cast<std::size_t>(2));
    std::size_t* ptr = &vec[0];
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
    }
    ASSERT_EQ(ptr, &vec[0]);
    ASSERT_EQ(vec[0], 2);
    ASSERT_EQ(vec.capacity(), iterations + 1);
    vec.push_back(static_cast<std::size_t>(3));
    ASSERT_EQ(vec.capacity(), (iterations + 1) * 2);
    ASSERT_NE(ptr, &vec[0]);
    ASSERT_EQ(vec[0], 2);
    ASSERT_EQ(vec[iterations + 1], 3);
    vec.reserve(vec.capacity() - 1);
    ASSERT_EQ(vec.capacity(), (iterations + 1) * 2);
}

TEST(Vector, shrink_to_fit) {
    pr::Vector<int> vec;
    ASSERT_EQ(vec.capacity(), 0);
    vec.reserve(100);
    ASSERT_EQ(vec.capacity(), 100);
    vec.push_back(1);
    vec.shrink_to_fit();
    ASSERT_EQ(vec.capacity(), 1);
    ASSERT_EQ(vec[0], 1);
    vec.reserve(10);
    ASSERT_EQ(vec.capacity(), 10);
    vec.push_back(2);
    vec.shrink_to_fit();
    ASSERT_EQ(vec.capacity(), vec.size());
}

TEST(Vector, dataTest) {
    pr::Vector<std::size_t> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
    }
    for (std::size_t i {0}; i < iterations; ++i) {
        ASSERT_EQ(vec.data()[i], i);
    }
}

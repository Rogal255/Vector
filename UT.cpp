#include "Vector.hpp"
#include <gtest/gtest.h>
#include <iostream>
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

// Also checks subscript operator
TEST(Vector, push_back) {
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
    ASSERT_EQ(vec.size(), 0);
    vec.reserve(100);
    ASSERT_EQ(vec.capacity(), 100);
    ASSERT_EQ(vec.size(), 0);
    vec.push_back(1);
    ASSERT_EQ(vec.size(), 1);
    vec.shrink_to_fit();
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec.capacity(), 1);
    ASSERT_EQ(vec.size(), 1);
    vec.reserve(10);
    ASSERT_EQ(vec.capacity(), 10);
    ASSERT_EQ(vec.size(), 1);
    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2);
    vec.shrink_to_fit();
    ASSERT_EQ(vec.capacity(), 2);
    ASSERT_EQ(vec.size(), 2);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}

TEST(Vector, dataTest) {
    pr::Vector<std::size_t> vec;
    ASSERT_EQ(vec.data(), nullptr);
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(i);
    }
    ASSERT_NE(vec.data(), nullptr);
    ASSERT_EQ(vec.data(), &vec[0]);
}

TEST(VectorOfBools, push_back) {
    pr::Vector<bool> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(static_cast<bool>(i % 2));
        ASSERT_TRUE(vec[i] == static_cast<bool>(i % 2));
    }
    ASSERT_EQ(vec.size(), iterations);
}

TEST(VectorOfBools, reserve) {
    pr::Vector<bool> vec;
    vec.reserve(10);
    ASSERT_EQ(vec.capacity(), 16);
    for (int i {0}; i < 16; ++i) {
        vec.push_back(true);
    }
    ASSERT_EQ(vec.capacity(), 16);
    vec.reserve(5);
    ASSERT_EQ(vec.capacity(), 16);
    vec.reserve(100);
    ASSERT_EQ(vec.capacity(), 104);
    vec.reserve(40);
    ASSERT_EQ(vec.capacity(), 104);
}

TEST(VectorOfBools, reallocationTest) {
    pr::Vector<bool> vec;
    constexpr std::size_t iterations {10000};
    for (std::size_t i {0}; i < iterations; ++i) {
        vec.push_back(static_cast<bool>(i % 2));
        ASSERT_TRUE(vec[i] == static_cast<bool>(i % 2));
    }
    for (std::size_t i {0}; i < iterations; ++i) {
        std::cout << "index: " << i << ", value: " << vec[i].get() << '\n';
    }
    for (std::size_t i {0}; i < iterations; ++i) {
        std::cout << "index: " << i << ", value: " << vec[i].get() << '\n';
        ASSERT_TRUE(vec[i] == static_cast<bool>(i % 2));
    }
}

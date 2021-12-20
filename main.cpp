#include "Vector.hpp"
#include <iostream>
#include <vector>

int main() {
    pr::Vector<int> myVec;
    std::cout << "Size: " << myVec.size() << '\n';
    std::cout << "Capacity: " << myVec.capacity() << '\n';
    std::cout << "---\n";
    for (std::size_t i {0}; i < 100; ++i) {
        myVec.push_back(1);
        std::cout << "Size: " << myVec.size() << '\n';
        std::cout << "Capacity: " << myVec.capacity() << '\n';
        std::cout << "---\n";
    }
    return 0;
}

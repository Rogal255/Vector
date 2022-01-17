#pragma once
#include <cstdint>

class boolReference {
public:
    boolReference(uint8_t& vectorElement, uint8_t elementPosition);
    explicit operator bool() const;

private:
    uint8_t& vectorElement_;
    uint8_t elementPosition_;
};

#pragma once
#include <cstdint>

class boolReference {
public:
    boolReference(uint8_t& vectorElement, uint8_t elementPosition);
    explicit operator bool() const;
    boolReference& operator=(bool rhs);
    boolReference& operator=(const boolReference& rhs);

    bool operator==(bool rhs) const;
    bool operator==(const boolReference& rhs) const;

private:
    uint8_t& vectorElement_;
    uint8_t elementPosition_;

    [[nodiscard]] bool get() const;
};

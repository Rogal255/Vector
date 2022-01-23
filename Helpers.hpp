#pragma once
#include <cstdint>

class boolReference {
public:
    boolReference(uint8_t& vectorElement, uint8_t elementPosition) noexcept;
    explicit operator bool() const noexcept;
    boolReference& operator=(bool rhs) noexcept;
    boolReference& operator=(const boolReference& rhs) noexcept;

    bool operator==(bool rhs) const noexcept;
    bool operator==(const boolReference& rhs) const noexcept;

private:
    uint8_t& vectorElement_;
    uint8_t elementPosition_;

    [[nodiscard]] bool get() const noexcept;
};

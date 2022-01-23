#include "Helpers.hpp"

boolReference::boolReference(uint8_t& vectorElement, uint8_t elementPosition) noexcept :
    vectorElement_ {vectorElement}, elementPosition_ {elementPosition} {};

boolReference::operator bool() const noexcept { return vectorElement_ & (1 << elementPosition_); }

boolReference& boolReference::operator=(bool rhs) noexcept {
    if (rhs) {
        vectorElement_ |= 1 << elementPosition_;
    } else {
        vectorElement_ &= ~(1 << elementPosition_);
    }
    return *this;
}

boolReference& boolReference::operator=(const boolReference& rhs) noexcept {
    *this = rhs.operator bool();
    return *this;
}

bool boolReference::operator==(bool rhs) const noexcept { return this->operator bool() == rhs; }
bool boolReference::operator==(const boolReference& rhs) const noexcept {
    return this->operator bool() == rhs.operator bool();
}

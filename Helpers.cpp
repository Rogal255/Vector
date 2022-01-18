#include "Helpers.hpp"

boolReference::boolReference(uint8_t& vectorElement, uint8_t elementPosition) :
    vectorElement_ {vectorElement}, elementPosition_ {elementPosition} {};

boolReference::operator bool() const { return vectorElement_ & (1 << elementPosition_); }

boolReference& boolReference::operator=(bool rhs) {
    if (rhs) {
        vectorElement_ |= 1 << elementPosition_;
    } else {
        vectorElement_ &= 0 << elementPosition_;
    }
    return *this;
}

boolReference& boolReference::operator=(const boolReference& rhs) { operator=(rhs.get()); }

bool boolReference::get() const { return vectorElement_ & (1 << elementPosition_); }

#include "Helpers.hpp"

boolReference::boolReference(uint8_t& vectorElement, uint8_t elementPosition) :
    vectorElement_ {vectorElement}, elementPosition_ {elementPosition} {};

boolReference::operator bool() const { return vectorElement_ & (1 << elementPosition_); }

boolReference& boolReference::operator=(bool rhs) {
    if (rhs) {
        vectorElement_ |= 1 << elementPosition_;
    } else {
        vectorElement_ &= ~(1 << elementPosition_);
    }
    return *this;
}

boolReference& boolReference::operator=(const boolReference& rhs) {
    *this = rhs.get();
    return *this;
}

bool boolReference::get() const { return vectorElement_ & (1 << elementPosition_); }

bool boolReference::operator==(bool rhs) const { return this->get() == rhs; }
bool boolReference::operator==(const boolReference& rhs) const { return this->get() == rhs.get(); }

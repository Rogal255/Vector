#include "Helpers.hpp"

boolReference::boolReference(uint8_t& vectorElement, uint8_t elementPosition) :
    vectorElement_ {vectorElement}, elementPosition_ {elementPosition} {};

boolReference::operator bool() const { return vectorElement_ & (1 << (elementPosition_ % 8)); }

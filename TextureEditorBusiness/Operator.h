#pragma once

#include "guiddef.h"
#include "combaseapi.h"

class Operator
{
private:
    _GUID* m_id;
public:
	Operator() {
        if (CoCreateGuid(m_id) != S_OK) {
            throw;
        }
    }
    _GUID* GetId() const {
        return m_id;
    }
};

// Macro to create a derived class
#define CREATE_OPERATOR_CLASS(className)      \
class className : public Operator {           \
public:                                       \
    className() : Operator() {}               \
};



#pragma once

#include "guiddef.h"
#include "combaseapi.h"

class Operator
{
private:
    _GUID* id;
public:
	Operator() {
        if (CoCreateGuid(id) != S_OK) {
            throw;
        }
    }
    _GUID* GetId() const {
        return id;
    }
};

// Macro to create a derived class
#define CREATE_OPERATOR_CLASS(className)      \
class className : public Operator {           \
public:                                       \
    className() : Operator() {}               \
};



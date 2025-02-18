#pragma once

#include "guiddef.h"
#include "combaseapi.h"

class DraftClient;

class Operator
{
private:
    _GUID* m_id = new _GUID();
public:
	Operator() {
        if (CoCreateGuid(m_id) != S_OK) {
            throw;
        }
    }
    _GUID* GetId() const {
        return m_id;
    }

    virtual void Activate(DraftClient*) {};
};

// Macro to create a derived class
#define CREATE_OPERATOR_CLASS(CLASSNAME)      \
class CLASSNAME : public Operator {           \
public:                                       \
    struct Data {};                           \
    CLASSNAME() : Operator() {}               \
    void Activate(DraftClient*) override {};  \
};

#pragma once

#include "guiddef.h"
#include "combaseapi.h"

class Draft
{
private:
    _GUID* id;
public:
	Draft() {
        if (CoCreateGuid(id) != S_OK) {
            throw;
        }
    }
    _GUID* GetId() const {
        return id;
    }
};

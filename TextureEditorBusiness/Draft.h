#pragma once

#include "guiddef.h"
#include "combaseapi.h"

class Draft
{
private:
    _GUID* m_id;
public:
	Draft() {
        if (CoCreateGuid(m_id) != S_OK) {
            throw;
        }
    }
    _GUID* GetId() const {
        return m_id;
    }
};

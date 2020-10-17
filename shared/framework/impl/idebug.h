#pragma once

#include <common/ztime.h>

class irender;

class idebug
{
public:
    virtual ~idebug();

    virtual void update(ztime ms) = 0;
    virtual void render(irender& render) = 0;
};
